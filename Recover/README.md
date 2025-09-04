# Recover

## Overview
This program recovers JPEG images from a forensic image of a memory card.  
It scans the card byte by byte (in 512-byte blocks) to detect JPEG signatures and reconstruct each photo.

## Objective
- Accept exactly one command-line argument: the name of the forensic image.  
- Identify JPEGs using their 4-byte signature:
  - First three bytes: `0xff 0xd8 0xff`
  - Fourth byte: `0xe0`–`0xef` (first four bits `1110`)
- Recover each JPEG in sequence and save them as `###.jpg` (e.g., `000.jpg`, `001.jpg`).  
- Properly handle memory and file streams, ensuring no memory leaks.

