#!/bin/bash

make all

echo "Ejecutando Hanoi de 4 torres y 18 discos con bfs"
./hanoi_4_18.bfs ../../benchmarks/hanoi_4p18d/hanoi_4p18d.d=005.txt >> results418_d5bfs.txt 
./hanoi_4_18.bfs ../../benchmarks/hanoi_4p18d/hanoi_4p18d.d=010.txt >> results418_d10bfs.txt
./hanoi_4_18.bfs ../../benchmarks/hanoi_4p18d/hanoi_4p18d.d=015.txt >> results418_d15bfs.txt
./hanoi_4_18.bfs ../../benchmarks/hanoi_4p18d/hanoi_4p18d.d=2000.txt >> results418_d2000bfs.txt
./hanoi_4_18.bfs ../../benchmarks/hanoi_4p18d/hanoi_4p18d.d=2000000.txt >> results418_d2000000bfs.txt



echo "Hanoi de 4 torres y 18 discos con ucs"
./hanoi_4_18.ucs ../../benchmarks/hanoi_4p18d/hanoi_4p18d.d=005.txt >> results418_d5ucs.txt 
./hanoi_4_18.ucs ../../benchmarks/hanoi_4p18d/hanoi_4p18d.d=010.txt >> results418_d10ucs.txt
./hanoi_4_18.ucs ../../benchmarks/hanoi_4p18d/hanoi_4p18d.d=015.txt >> results418_d15ucs.txt
./hanoi_4_18.ucs ../../benchmarks/hanoi_4p18d/hanoi_4p18d.d=2000.txt >> results418_d2000ucs.txt
./hanoi_4_18.ucs ../../benchmarks/hanoi_4p18d/hanoi_4p18d.d=2000000.txt >> results418_d2000000ucs.txt
