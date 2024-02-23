#!/bin/bash

make all

echo "Ejecutando Rubik con bfs"
./rubik3Sticker.bfs ../../benchmarks/rubik3/rubik3.d=005.txt >> resultsRubik_d5bfs.txt 
./rubik3Sticker.bfs ../../benchmarks/rubik3/rubik3.d=010.txt >> resultsRubik_d10bfs.txt
./rubik3Sticker.bfs ../../benchmarks/rubik3/rubik3.d=015.txt >> resultsRubik_d15bfs.txt
./rubik3Sticker.bfs ../../benchmarks/rubik3/rubik3.d=020.txt >> resultsRubik_d20bfs.txt
./rubik3Sticker.bfs ../../benchmarks/rubik3/rubik3.d=040.txt >> resultsRubik_d40bfs.txt
./rubik3Sticker.bfs ../../benchmarks/rubik3/rubik3.d=080.txt >> resultsRubik_d80bfs.txt
./rubik3Sticker.bfs ../../benchmarks/rubik3/rubik3.d=160.txt >> resultsRubik_d160bfs.txt


echo "Ejecutando Rubik con ucs"
./rubik3Sticker.ucs ../../benchmarks/rubik3/rubik3.d=005.txt >> resultsRubik_d5ucs.txt 
./rubik3Sticker.ucs ../../benchmarks/rubik3/rubik3.d=010.txt >> resultsRubik_d10ucs.txt
./rubik3Sticker.ucs ../../benchmarks/rubik3/rubik3.d=015.txt >> resultsRubik_d15ucs.txt
./rubik3Sticker.ucs ../../benchmarks/rubik3/rubik3.d=020.txt >> resultsRubik_d20ucs.txt
./rubik3Sticker.ucs ../../benchmarks/rubik3/rubik3.d=040.txt >> resultsRubik_d40ucs.txt
./rubik3Sticker.ucs ../../benchmarks/rubik3/rubik3.d=080.txt >> resultsRubik_d80ucs.txt
./rubik3Sticker.ucs ../../benchmarks/rubik3/rubik3.d=160.txt >> resultsRubik_d160ucs.txt
