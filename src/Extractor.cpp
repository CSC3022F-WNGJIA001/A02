/**
* Extractor.cpp containing main function
* CSC3022F Assignment 2 2021
* Author: WNGJIA001
*/
#include <fstream>  
#include <iostream> 
#include <sstream>  
#include <string>
#include <vector>

#include "CmdLineParser.h"
#include "FrameSequence.h"
#include "FrameExtraction.h"

int main(int argc, char *argv[]) {
    using namespace WNGJIA001;
    ParseCmdLine(argc, argv);
    extractFrames();
    return 0;
}