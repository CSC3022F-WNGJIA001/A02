/**
* CmdLineParser.h 
* CSC3022F Assignment 2 2021
* Author: WNGJIA001
*/

#ifndef _CMDLINEPARSER
#define _CMDLINEPARSER

#include <iostream>
#include <string>
#include <vector>

namespace WNGJIA001 {
    // variables
    extern std::string pgm_filename;
    extern std::vector<int> t_coords;
    extern int width;
    extern int height;
    extern std::vector<std::string> w_ops;
    extern std::vector<std::string> w_names;
    extern int p_n;
    extern std::vector<int> p_coords;
    // Methods
    void GetHelp();
    void ParseCmdLine(int argc, char *argv[]);
    bool isNumber(const std::string& s);
    bool validOperation(const char* s);
    bool missingFlag();
}

#endif