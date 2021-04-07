# Makefile for Assignment 2 CSC3022F 2021
# Author: WNGJIA001

# variable definition
CC = g++
BINDIR = bin/
SRCDIR = src/
BUILDDIR = build/
CFLAGS = -c -Wall -Iinclude
rm = rm -f
# target and objects declaration
TARGET = $(BUILDDIR)extractor
OBJECTS = $(BINDIR)CmdLineParser.o $(BINDIR)FrameSequence.o $(BINDIR)FrameExtraction.o $(BINDIR)Extractor.o

# link object files to create executable file extractor
$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ -std=c++2a
# compile source files to create object files
$(BINDIR)%.o: $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $< -o $@ -std=c++2a

# remove all the object binary files and executable file
clean:
	$(rm) $(BINDIR)*.o $(BINDIR)*.pgm
	$(rm) $(BUILDDIR)extractor