/**
* FrameSequence.cpp source file for FrameSequence.h
* CSC3022F Assignment 2 2021
* Author: WNGJIA001
*/

#include <string>
#include <vector>
#include <cmath>

#include "FrameSequence.h"
#include "CmdLineParser.h"
#include "FrameExtraction.h"

namespace WNGJIA001 {
    FrameSequence::FrameSequence(void) {
        frm_count = 0;
    }

    void FrameSequence::setFrameSize(int width, int height) { 
        frm_width = width;
        frm_height = height;
    }

    void FrameSequence::extractFrames(char *img_arr) {
        if (p_coords.empty()) {
            // single path from t_coords
            fillImageSequence(t_coords[0], t_coords[1], t_coords[2], t_coords[3], img_arr);
        } else {
            // loop polyline through p_coords
            for (int i = 0; i < (p_n-1); ++i) {
                int start = i*2;
                fillImageSequence(p_coords[start], p_coords[start+1], p_coords[start+2], p_coords[start+3], img_arr);
            }
        }
    }

    void FrameSequence::fillImageSequence(int x_start, int y_start, int x_end, int y_end, char *img_arr) {
        unsigned char ** frm_ptr;
        float delta_y = y_end - y_start;
        float delta_x = x_end - x_start;
        if (delta_x == 0.0) {
            // horizontally moving from left to right
            int x = x_start;
            for (int y = y_start; y <= y_end; ++y) {
                frm_ptr = new unsigned char * [frm_height];
                for (int i = 0; i < frm_height; ++i) {
                    frm_ptr[i] = new unsigned char[frm_width];
                    for (int j = 0; j < frm_width; ++j) {
                        int pos = ((x+i)*img_width)+(y+j); 
                        frm_ptr[i][j] = unsigned(img_arr[pos]);
                    }
                }
                imageSequence.push_back(frm_ptr);
                // increment frame count and y
                frm_count += 1;
            }
        } else {
            float g = delta_y/delta_x;
            if (std::fabs(g) == 0.0) {
                // vertically moving downwards
                int y = y_start;
                for (int x = x_start; x <= x_end; ++x) {
                    frm_ptr = new unsigned char * [frm_height];
                    for (int i = 0; i < frm_height; ++i) {
                        frm_ptr[i] = new unsigned char[frm_width];
                        for (int j = 0; j < frm_width; ++j) {
                            int pos = ((x+i)*img_width)+(y+j); 
                            frm_ptr[i][j] = unsigned(img_arr[pos]);
                        }
                    }
                imageSequence.push_back(frm_ptr);
                // increment frame count and y
                frm_count += 1;
                }
            } else if (std::fabs(g) < 1.0) {
                // use x loop variable, to find y
                float y = y_start;
                for (int x = x_start; x <= x_end; ++x) {
                    frm_ptr = new unsigned char * [frm_height];
                    for (int i = 0; i < frm_height; ++i) {
                        frm_ptr[i] = new unsigned char[frm_width];
                        for (int j = 0; j < frm_width; ++j) {
                            int pos = (x+i)*img_width+(round(y)+j); 
                            frm_ptr[i][j] = unsigned(img_arr[pos]);
                        }
                    }
                    imageSequence.push_back(frm_ptr);
                    // increment frame count and y
                    frm_count += 1;
                    y += g;
                }
            } else if (std::fabs(g) > 1.0) {
                // use y loop variable to find x
                float x = x_start;
                for (int y = y_start; y <= y_end; ++y) {
                    frm_ptr = new unsigned char * [frm_height];
                    for (int i = 0; i < frm_height; ++i) {
                        frm_ptr[i] = new unsigned char[frm_width];
                        for (int j = 0; j < frm_width; ++j) {
                            int pos = (round(x)+i)*img_width+(y+j); 
                            frm_ptr[i][j] = unsigned(img_arr[pos]);
                        }
                    }
                    imageSequence.push_back(frm_ptr);
                    // increment frame count and y
                    frm_count += 1;
                    x += (1/g);
                }
            }
        }
    }

    int FrameSequence::getFrameCount(void) {
        return frm_count;
    }

    char FrameSequence::getPixel(int i, int row, int col) {
        char pixel = imageSequence[i][row][col];
        return pixel;
    }

    FrameSequence::~FrameSequence() {
        // Clean up imageSequence
        for(int i = 0; i < imageSequence.size(); ++i) {
            for(int row = 0; row < frm_height; ++row) {
		        delete [] imageSequence[i][row];
                // std::cout << "===== pointer pointing to imageSequence[" << i << "][" << row << "] deleted =====" << std::endl;
	        }
            delete [] imageSequence[i];
            // std::cout << "***** pointer pointing to imageSequence[" << i << "] deleted *****" << std::endl;
        }
        imageSequence.clear();
    }
}