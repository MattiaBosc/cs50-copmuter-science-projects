# Volume

## Overview
This project modifies the volume of WAV audio files.  
It reads 16-bit audio samples from an input file, scales them by a specified factor, and writes the result to a new output file.

## Objective
- Implement a program in C (`volume.c`) inside a folder named `volume`.  
- Accept three command-line arguments:  
  1. Input WAV file name  
  2. Output WAV file name  
  3. Volume scaling factor (float)  
- Read the WAV header from the input file and write it to the output file.  
- Multiply each 16-bit audio sample by the factor and write the result to the output file.  
- Ensure no memory leaks if using dynamic memory allocation.
