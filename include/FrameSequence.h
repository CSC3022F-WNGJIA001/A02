/**
* FrameSequence.h 
* CSC3022F Assignment 2 2021
* Author: WNGJIA001
*/
#ifndef _FRAMESEQUENCE
#define _FRAMESEQUENCE

#include <string>
#include <vector>
#include <cmath>

namespace WNGJIA001 {
    // FrameSequence class stores each extracted frame image as a dynamically allocated unsigned char array
    class FrameSequence {
        private:
            // each element of the vector stores a pointer to a dynamically allocated 2D image frame
            std::vector<unsigned char **> imageSequence;
            int frm_count;
            int frm_width;
            int frm_height;
        public:
            FrameSequence(void); // Constructor
            void setFrameSize(int width, int height);
            void extractFrames(char *img_arr);
            void fillImageSequence(int x_start, int y_start, int x_end, int y_end, char *img_arr);
            int getFrameCount(void);
            char getPixel(int i, int row, int col);
            ~FrameSequence(); // Destuctor
    };
}

#endif