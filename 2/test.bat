@echo off
@echo Test %2
@echo Test %2 >> result.txt
copy %2.in euler.in > nul
Timer %1 20000 65536 >> result.txt
Checker %2 >> result.txt
if exist euler.in del euler.in
if exist euler.out del euler.out