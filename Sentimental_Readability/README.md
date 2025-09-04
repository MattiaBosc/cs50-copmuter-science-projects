# Sentimental Readability

This Python program calculates the reading grade level of a text using the Coleman-Liau index, similar to CS50’s Problem Set 2. Users input a passage of text, and the program outputs the approximate U.S. school grade level required to understand it.

## How It Works

1. The program prompts the user to enter some text.
2. It counts the number of letters, words, and sentences in the text.
   - Letters: any uppercase or lowercase alphabetical character (A–Z, a–z)
   - Words: sequences of characters separated by spaces
   - Sentences: any occurrence of `.`, `!`, or `?`
3. It calculates the Coleman-Liau index: index = 0.0588 * L - 0.296 * S - 15.8

where:
- L is the average number of letters per 100 words
- S is the average number of sentences per 100 words

4. The program prints the grade level:
- If the index ≥ 16 → "Grade 16+"
- If the index < 1 → "Before Grade 1"
- Otherwise → "Grade X" (rounded to nearest integer)
