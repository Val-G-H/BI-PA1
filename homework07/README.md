# Introduction

## Assignment:

Refer to the [assignment details here](assignment.txt)

## Current solution

Refer to [implementation here](hw01_hard.c)

## Tests

Local tests via terminal script

`for file in CZE/*_in.txt; do echo "$file"; ./a.out < "$file" | diff - "${file/in/out}"; done`
