/**
* CmdLineParser.cpp source file for CmdLineParser.h
* CSC3022F Assignment 2 2021
* Author: WNGJIA001
*/

#include <iostream> 
#include <string>
#include <vector>
#include "CmdLineParser.h"

namespace WNGJIA001 {
    std::string pgm_filename;
    std::vector<int> t_coords;
    int width = 0;
    int height = 0;
    std::vector<std::string> w_ops;
    std::vector<std::string> w_names;
    int p_n = 0;
    std::vector<int> p_coords;

    void GetHelp() {
        std::cout << "Usage:\t\t\t\t./extractor <inputPGMfile> [options]\n\nOptions are:" << std::endl;
		std::cout << "-t <int> <int> <int> <int>\t# x1 y1 x2 y2 (begin & end origin pixel coords, for frame trajectory)" << std::endl;
        std::cout << "-s <int> <int>\t\t\t# <width> <height> (size of small frame in pixels)" << std::endl;
        std::cout << "-w <string> <string>\t\t# write frames with <operation> <name>" << std::endl;
    }
    
    void ParseCmdLine(int argc, char *argv[]) {
        if(argc == 1) { // no command line flags: error
            std::cerr << "ERROR: No Command Line Option Found. Type in --help or -h" << std::endl;
            exit(1);
        } else if (argc == 2){ // -h or --help flag: show flag options; otherwise: error
            if(!std::strcmp(argv[1], "-h") || !std::strcmp(argv[1], "--help")) {
			    GetHelp();
			    exit(0);
            } else { 
                std::cerr << "ERROR: Undefined Command Line Flags" << std::endl;
            }
        } else { // parse command line arguments
            // checking validity of the filename
            pgm_filename = argv[1]; 
            int filename_sz = pgm_filename.size();
            if (filename_sz < 5) { // minimum requirement is 5 chars, e.g: a.pgm
                std::cerr << "ERROR: Invalid PGM Filename" << std::endl;
                exit(1);
            } else if (pgm_filename.find('.') != std::string::npos) {
                std::string extension = pgm_filename.substr(pgm_filename.find('.')+1);
                if (extension != "pgm") { // incorrect extension 
                    std::cerr << "ERROR: Invalid PGM Filename" << std::endl;
                    exit(1);
                }
            } else { // size > 4 but no extension 
                std::cerr << "ERROR: Invalid PGM Filename" << std::endl;
                exit(1);
            } 
            // parse command line flags
            int i = 2;
            while (i < argc) {
                if (!std::strcmp(argv[i], "-t")) {
                    if (!t_coords.empty()) { // multiple -t flags
                        std::cerr << "ERROR: Multiple Declaration of -t Flags" << std::endl;
                        exit(1);
                    } else if ((argc - i) < 5) { // require 4 params follow -t
                        std::cerr << "ERROR: Incorrect Format of -t Flags" << std::endl;
                        exit(1);
                    } else { // parse -t coords
                        for (int j = 0; j < 4; ++j) { // check if following 4 args are ints
                            if (isNumber(argv[i+1])) {
                                t_coords.push_back(std::stoi(argv[++i])); // it is assumed that always x_start < x_end & y_start < y_end
                            } else {
                                std::cerr << "ERROR: Incorrect Format of -t Flags" << std::endl;
                                exit(1);
                            }
                        }    
                    }
                } else if (!std::strcmp(argv[i], "-s")) {
                    if (width != 0 || height != 0) { // if width and height alrready assigned: multiple -s flags
                        std::cerr << "ERROR: Multiple Declaration of -s Flags" << std::endl;
                        exit(1);
                    } else if ((argc - i) < 3 || !isNumber(argv[i+1]) || !isNumber(argv[i+2])) { // if any pram not int: error
                        std::cerr << "ERROR: Incorrect Format of -s Flags." << std::endl;
                        exit(1);
                    } else { // parse -s flags
                        width = std::stoi(argv[++i]);
                        height = std::stoi(argv[++i]);                        
                    }
                } else if (!std::strcmp(argv[i], "-w")) {
                    if ((argc - i) < 3) { // require 2 params follow -w
                        std::cerr << "ERROR: Incorrect Format of -w Flags" << std::endl;
                        exit(1);
                    } else if (!validOperation(argv[i+1])) { // not a valid operation flag: error
                        std::cerr << "ERROR: Invalid -w Operation Flag" << std::endl;
                        exit(1);
                    } else { // parse -w flags
                        w_ops.push_back(argv[++i]);
                        w_names.push_back(argv[++i]);
                    }
                } else if (!std::strcmp(argv[i], "-p")) {
                    if (!p_coords.empty()) { // multiple -p flags
                        std::cerr << "ERROR: Multiple Declaration of -p Flags" << std::endl;
                        exit(1);
                    } 
                    if (isNumber(argv[i+1])) { // parse p_n
                        p_n = std::stoi(argv[++i]);
                        if ((argc - i) < 2*p_n+1) { // require 2*p_n params follow -p flag
                            std::cerr << "ERROR: Insufficient Number of -p Parameters" << std::endl;
                            exit(1);
                        }
                        for (int j = 0; j < 2*p_n; ++j) { // check if following 4 args are ints
                            if (isNumber(argv[i+1])) {
                                p_coords.push_back(std::stoi(argv[++i])); // it is assumed that always x_start < x_end & y_start < y_end
                            } else {
                                std::cerr << "ERROR: Incorrect Format of -p Flags." << std::endl;
                                exit(1);
                            }
                        }       
                    } else {
                        std::cerr << "ERROR: Incorrect Format of -p Flags." << std::endl;
                        exit(1);
                    }
                } else {
                    std::cerr << "ERROR: Undefined Command Line Flags" << std::endl;
                    exit(1);
                }
                ++i;
            }
            if (missingFlag()) {
                std::cerr << "ERROR: Missing Command Line Flags" << std::endl;
                exit(1);
            }
        }
    }

    bool isNumber(const std::string& s) {
        return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }

    bool validOperation(const char* s) {
        return !std::strcmp(s, "none") || !std::strcmp(s, "invert") || !std::strcmp(s, "reverse") || !std::strcmp(s, "revinvert");
    }

    bool missingFlag() {
        return (t_coords.empty() && p_coords.empty()) || (width == 0 || height == 0) || (w_ops.empty() || w_names.empty());
    }
}