#!/bin/bash

make all

echo "Ejecutando 15 puzzle con bfs"
./15puzzle.bfs ../../benchmarks/15-puzzle/15_puzzle_100_instances_korf.txt >> results15bfs.txt 

echo "Ejecutando 15puzzle con ucs"
./15puzzle.ucs ../../benchmarks/15-puzzle/15_puzzle_100_instances_korf.txt >> results15ucs.txt 