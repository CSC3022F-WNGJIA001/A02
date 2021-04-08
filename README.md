# Assignment 2 CSC3022F, 2021
# Author: WNGJIA001

----------------------------------------------------------------------------------------------
## Source Files
### CmdLineParser.cpp
Contains functions to parse the command line arguments 

### FrameSequence.cpp
Contains class frameSequence which creates a vector of unsigned char pointers to pointers as imageSequence; 
Each element of the vector stores a pointer to a dynamically allocated 2D image frame; 
FrameSequence has class functions to fill the imageSequence vector 

### FrameExtraction.cpp
Contains function to read input file as a dynamically allocated char array and create a FrameSequence object 
to generate the vector of frame sequence; The function then writes each frame as output pgm files 

### Extractor.cpp
Contains main function that calls functions from other source files 
----------------------------------------------------------------------------------------------
## Code Structure
Extractor.cpp calls functions from CmdLineParser.cpp and FrameExtraction.cpp which parses the command line 
flags and extracts frames from the input image; 
CmdLineParser.cpp also implements error checking when parsing the command line flags; 
Messages are displayed and program is terminated when errors are detetcted in the parsed flags;
FrameExtraction.cpp performs functions to read and write pgm files; also creates a FrameSequence object and calls 
its function to extract frames from input pgm file and fill the imageSequence vector.
After frame extraction, dynamically allocated 2D image frames stored in the vector are then generated as output pgm files.

### Mastery Work
Poly-line trajectory has been implemented; 
Deceleration/acceleration function was not implemented.
----------------------------------------------------------------------------------------------
## Makefile

```sh
$ make clean
```
Removes binary object files and pgm files from bin/ and executable file 'extractor' from build/ 

```sh
$ make
```
Compiles source files and store object files as bin/%.o; Links object files and store the executable 
file as build/extractor 
----------------------------------------------------------------------------------------------
## Run the extractor
### Example
```sh
$ ./build/extractor larger_image.pgm -p 5 0 0 40 50 80 120 200 200 400 500 -s 640 400 -w reverse sequence 
```
The above example generates frames extracted from larger_image.pgm following a poly-line trajectory among 
5 sets of coordinates of (0,0)->(40,50)->(80,120)->(200,200)->(400,500); Each frame will have a width of 
640 pixels and a height of 400 pixels; The output frame sequence will be reversed, i.e. frames written out 
from last to first, the ith frame would be then stored as sequence-000i.pgm 

### Available Flags
```sh
$ -t <int> <int> <int> <int>
```
Specifies x1 y1 x2 y2 (begin & end origin pixel coordinates, for frame trajectory); 
Only one -t flag should be specified

```sh
$ -s <int> <int>
```
Specifies width height (size of frame in pixels); 
Only one -s flag should be specified

```sh
$ -w <string> <string>
```
Specifies operation name (operation to be performed on the frames and name of which the output pgm files should be named); 
Multiple -w flags can be specified for multiple pairs of operations and names

```sh
$ -p <int n> <int(1)> <int(2)> ... <int(2*n)>
```
Specifies n x1 y1 x2 y2 ... xn yn (begin & end origin pixel coordinates, for poly-line frame trajectory); 
Only one -p flag should be specified and this flag will override -t flag 
----------------------------------------------------------------------------------------------
## Generate Video
### Example
```sh
$ ffmpeg -r 25 -s 800x400 -i bin/sequence-%04d.pgm -vcodec libx264 -pix_fmt yuv420p bin/output.mp4 
```
The above example will convert the pgm files of output frames named with the format sequence-%04d.pgm into 
a short video named output.mp4 