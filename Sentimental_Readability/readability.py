from cs50 import get_string
from string import ascii_letters

text = get_string("Text: ")

words = len(text.split())
sentences = letters = 0

for i in text:
    if i == '.' or i == '!' or i == '?':
        sentences += 1
    elif i in ascii_letters:
        letters += 1

sentences = sentences * 100 / words
letters = letters * 100 / words
index = round(0.0588 * letters - 0.296 * sentences - 15.8, 0)

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
