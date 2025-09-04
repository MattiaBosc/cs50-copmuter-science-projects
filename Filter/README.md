# Filter

## Overview
This project applies image filters to 24-bit BMP files.  
Users can transform images using grayscale, sepia, horizontal reflection, or blur effects.

## Objective
- Implement image filtering functions in C (`helpers.c`) inside a folder named `filter-less`.  
- Each function receives a 2D array of pixels (`RGBTRIPLE`) and modifies it in-place:  
  - `grayscale`: convert the image to black and white.  
  - `sepia`: apply a sepia tone.  
  - `reflect`: flip the image horizontally.  
  - `blur`: apply a box blur to the image.  
- Preserve the BMP file headers and structure.  

