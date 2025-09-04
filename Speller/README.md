# Speller

## Overview
This program implements a spell checker in C using a hash table.  
It loads a dictionary of words into memory, then checks a text file for misspellings.

## Objective
- Implement `dictionary.c` functions: `load`, `hash`, `size`, `check`, and `unload`.
- Use a hash table to store dictionary words efficiently.
- Ensure `check` is case-insensitive and only returns `true` for exact dictionary words.

## Key Functions
- `bool load(const char *dictionary)`:  
  Loads dictionary into memory and returns `true` if successful.
- `unsigned int hash(const char *word)`:  
  Maps a word to an index in the hash table.
- `unsigned int size(void)`:  
  Returns the number of words loaded into memory.
- `bool check(const char *word)`:  
  Returns `true` if `word` is in the dictionary, `false` otherwise.
- `bool unload(void)`:  
  Frees all memory used by the dictionary.

## Hash Table
- You may choose the number of buckets (`N`) and design your own hash function.
- Must handle collisions (e.g., via linked lists).

