/**
* FrameExtraction.cpp source file for FrameExtraction.h
* CSC3022F Assignment 2 2021
* Author: WNGJIA001
*/

#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "FrameExtraction.h"
#include "FrameSequence.h"
#include "CmdLineParser.h"

namespace WNGJIA001 {
    int img_width;
    int img_height;
    void extractFrames() {
        // extract frames with given parameters (from CmdLineParser) and generate output pgm files
        char *img_arr; // pointer to char array which stores binary data from original pgm file
        char *frm_arr; // pointer to char array which stores data of each frame imageSequence[i] from the frameSequence class 
        // open and read pgm file
        std::ifstream input_file(pgm_filename, std::ios::binary);
        if (input_file) {
            std::string input_line;
            while (!input_file.eof()) {
                std::getline(input_file, input_line);
                if (input_line == "P5") { continue; }
                else if (input_line.at(0) == '#') { continue; }
                else if (input_line == "255") { break; }
                else { 
                    std::istringstream line_ss(input_line);
                    line_ss >> img_width >> std::ws >> img_height >> std::ws;
                }
            }
            // read the binary data of the input pgm file
            img_arr = new char[img_width*img_height];
            input_file.read(img_arr, img_width*img_height);

            // extract frame sequence
            FrameSequence frameSequence;
            frameSequence.setFrameSize(width, height);
            frameSequence.extractFrames(img_arr);

            // clean up memory memory for the input PGM image after frame extraction
            delete [] img_arr;

            // write output pgm files for each w operation
            for (int w_i = 0; w_i < w_ops.size(); ++w_i) {
                std::string w_op = w_ops[w_i];
                std::string w_name = w_names[w_i];
                for (int i = 0; i < frameSequence.getFrameCount(); ++i) {
                    // loop through each frame and apply the operation
                    frm_arr = new char[width*height];
                    // fill frm_arr
                    for (int row = 0; row < height; ++row) {
                        for (int col = 0; col < width; ++col) {
                            int pos = row*width + col;
                            if (w_op == "none") {
                                frm_arr[pos] = frameSequence.getPixel(i, row, col);
                            } else if (w_op == "invert") {
                                unsigned char a = 255;
                                frm_arr[pos] = a - frameSequence.getPixel(i, row, col);
                            } else if (w_op == "reverse") {
                                pos = (width*height-1) - pos;
                                frm_arr[pos] = frameSequence.getPixel(i, row, col);
                            } else if (w_op == "revinvert") {
                                pos = (width*height-1) - pos;
                                unsigned char a = 255;
                                frm_arr[pos] = a - frameSequence.getPixel(i, row, col);
                            } 
                        }
                    }
                    // write to output file
                    std::ostringstream code_ss;
                    code_ss << std::setfill('0') << std::setw(4) << i;
                    std::string output_filename = "bin/" + w_name + "-" + code_ss.str() + ".pgm";
                    std::ofstream output_file(output_filename, std::ios_base::binary);
                    output_file << "P5\n" << width << " " << height << "\n" <<  "255\n"; 
                    output_file.write(frm_arr, width*height);
                    output_file.close();
                    // clean up memory of each frame array pointer
                    delete [] frm_arr;
                }
            }
        } else {
            std::cerr << "ERROR: " << pgm_filename << " can not be found" << std::endl;
        }
        // close pgm file
        input_file.close();
    }
}