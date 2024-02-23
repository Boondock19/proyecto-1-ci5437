#!/bin/bash

make all

echo "Ejecutando Hanoi de 4 torres y 14 discos con bfs"
./hanoi_4_14.bfs ../../benchmarks/hanoi_4p14d/hanoi_4p14d.d=005.txt >> results414_d5bfs.txt 
./hanoi_4_14.bfs ../../benchmarks/hanoi_4p14d/hanoi_4p14d.d=010.txt >> results414_d10bfs.txt
./hanoi_4_14.bfs ../../benchmarks/hanoi_4p14d/hanoi_4p14d.d=015.txt >> results414_d15bfs.txt
./hanoi_4_14.bfs ../../benchmarks/hanoi_4p14d/hanoi_4p14d.d=2000.txt >> results414_d2000bfs.txt
./hanoi_4_14.bfs ../../benchmarks/hanoi_4p14d/hanoi_4p14d.d=2000000.txt >> results414_d2000000bfs.txt



echo "Ejecutando Hanoi de 4 torres y 14 discos con ucs"
./hanoi_4_14.ucs ../../benchmarks/hanoi_4p14d/hanoi_4p14d.d=005.txt >> results414_d5ucs.txt 
./hanoi_4_14.ucs ../../benchmarks/hanoi_4p14d/hanoi_4p14d.d=010.txt >> results414_d10ucs.txt
./hanoi_4_14.ucs ../../benchmarks/hanoi_4p14d/hanoi_4p14d.d=015.txt >> results414_d15ucs.txt
./hanoi_4_14.ucs ../../benchmarks/hanoi_4p14d/hanoi_4p14d.d=2000.txt >> results414_d2000ucs.txt
./hanoi_4_14.ucs ../../benchmarks/hanoi_4p14d/hanoi_4p14d.d=2000000.txt >> results414_d2000000ucs.txt
