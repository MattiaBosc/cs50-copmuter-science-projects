# Readability

## Overview
This project calculates the approximate U.S. grade level required to comprehend a given text.  
It uses the Coleman-Liau index to determine the readability based on the average number of letters and sentences per 100 words.

## Objective
- Prompt the user to input a block of text.  
- Compute the grade level according to the Coleman-Liau formula: index = 0.0588 * L - 0.296 * S - 15.8
where `L` is the average number of letters per 100 words, and `S` is the average number of sentences per 100 words.  
- Print the result as:
- `Grade X` for levels 1–15, rounded to the nearest integer.  
- `Grade 16+` for grade levels 16 or higher.  
- `Before Grade 1` if the computed grade is less than 1.
