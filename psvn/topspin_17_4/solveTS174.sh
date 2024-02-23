#!/bin/bash

make all

echo "Ejecutando Top Spin de 4 piezas centrales y 17 piezas totales con bfs"
./topspin_17_4.bfs ../../benchmarks/topspin_17_4/topspin_17_4.d=005.txt >> results174_d5bfs.txt 
./topspin_17_4.bfs ../../benchmarks/topspin_17_4/topspin_17_4.d=010.txt >> results174_d10bfs.txt
./topspin_17_4.bfs ../../benchmarks/topspin_17_4/topspin_17_4.d=015.txt >> results174_d15bfs.txt
./topspin_17_4.bfs ../../benchmarks/topspin_17_4/topspin_17_4.d=2000.txt >> results174_d2000bfs.txt
./topspin_17_4.bfs ../../benchmarks/topspin_17_4/topspin_17_4.d=2000000.txt >> results174_d2000000bfs.txt



echo "Ejecutando Top Spin de 4 piezas centrales y 17 piezas totales con ucs"
./topspin_17_4.ucs ../../benchmarks/topspin_17_4/topspin_17_4.d=005.txt >> results174_d5ucs.txt 
./topspin_17_4.ucs ../../benchmarks/topspin_17_4/topspin_17_4.d=010.txt >> results174_d10ucs.txt
./topspin_17_4.ucs ../../benchmarks/topspin_17_4/topspin_17_4.d=015.txt >> results174_d15ucs.txt
./topspin_17_4.ucs ../../benchmarks/topspin_17_4/topspin_17_4.d=2000.txt >> results174_d2000ucs.txt
./topspin_17_4.ucs ../../benchmarks/topspin_17_4/topspin_17_4.d=2000000.txt >> results174_d2000000ucs.txt
