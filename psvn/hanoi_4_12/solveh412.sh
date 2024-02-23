#!/bin/bash

make all

echo "Ejecutando Hanoi de 4 torres y 12 discos con bfs"
./hanoi_4_12.bfs ../../benchmarks/hanoi_4p12d/hanoi_4p12d.d=005.txt >> results412_d5bfs.txt 
./hanoi_4_12.bfs ../../benchmarks/hanoi_4p12d/hanoi_4p12d.d=010.txt >> results412_d10bfs.txt
./hanoi_4_12.bfs ../../benchmarks/hanoi_4p12d/hanoi_4p12d.d=015.txt >> results412_d15bfs.txt
./hanoi_4_12.bfs ../../benchmarks/hanoi_4p12d/hanoi_4p12d.d=2000.txt >> results412_d2000bfs.txt
./hanoi_4_12.bfs ../../benchmarks/hanoi_4p12d/hanoi_4p12d.d=2000000.txt >> results412_d2000000bfs.txt



echo "Ejecutando Hanoi de 4 torres y 12 discos con ucs"
./hanoi_4_12.ucs ../../benchmarks/hanoi_4p12d/hanoi_4p12d.d=005.txt >> results412_d5ucs.txt 
./hanoi_4_12.ucs ../../benchmarks/hanoi_4p12d/hanoi_4p12d.d=010.txt >> results412_d10ucs.txt
./hanoi_4_12.ucs ../../benchmarks/hanoi_4p12d/hanoi_4p12d.d=015.txt >> results412_d15ucs.txt
./hanoi_4_12.ucs ../../benchmarks/hanoi_4p12d/hanoi_4p12d.d=2000.txt >> results412_d2000ucs.txt
./hanoi_4_12.ucs ../../benchmarks/hanoi_4p12d/hanoi_4p12d.d=2000000.txt >> results412_d2000000ucs.txt
