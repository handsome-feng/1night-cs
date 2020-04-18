---
title: Vargrind quick start quide
---

## Preparing your program

Compile with -g -O0

## Running

valgrind --leak-check=yes --track-origins=yes myprog arg1 arg2