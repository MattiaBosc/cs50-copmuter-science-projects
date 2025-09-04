# Inheritance

## Overview
This program simulates the inheritance of blood types across generations of a family.  
Each person has two alleles (A, B, or O) and inherits one allele from each parent.

## Objective
- Create a family tree of a specified number of generations.
- The oldest generation receives alleles randomly.
- Each subsequent generation inherits one allele from each parent.
- Each person has two parents (except the oldest generation, whose parents are `NULL`).

## Key Functions
- `create_family(int generations)`:  
  Allocates memory for a family of `generations` and returns a pointer to the youngest generation.
- `random_allele()`:  
  Returns a randomly chosen allele (`A`, `B`, or `O`) for the oldest generation.
- `free_family(person *p)`:  
  Frees memory allocated for the family tree recursively.

