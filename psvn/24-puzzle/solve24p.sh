#!/bin/bash

make all

echo "Ejecutando 24 puzzle con bfs"
./24puzzle.bfs ../../benchmarks/15-puzzle/24_puzzle_50_instances_korf.txt >> results24bfs.txt 

echo "Ejecutando 24puzzle con ucs"
./24puzzle.ucs ../../benchmarks/15-puzzle/24_puzzle_50_instances_korf.txt >> results24ucs.txt 