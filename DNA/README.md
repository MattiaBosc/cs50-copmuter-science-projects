# DNA Matching

This Python program identifies the owner of a DNA sequence by comparing Short Tandem Repeats (STRs) to a database of known individuals, similar to CS50’s DNA problem set.

## How It Works

1. The program takes **two command-line arguments**:
   - A CSV file containing STR counts for each individual
   - A text file containing a DNA sequence to identify

2. The CSV file is read into memory. The first row contains column names: `name` followed by STR sequences.

3. The DNA sequence is read into memory.

4. For each STR, the program calculates the **longest run of consecutive repeats** in the DNA sequence using the provided `longest_match` function.

5. It compares the STR counts to each individual in the CSV:
   - If an exact match is found, the program prints the individual's name.
   - If no match is found, the program prints `No match`.

