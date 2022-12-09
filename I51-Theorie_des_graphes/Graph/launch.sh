#!/bin/bash
clear

make -BC lib
make -BC test prog.exe

#> partition.dat
#
#for i in {1..100}
#do
#  #/usr/bin/time --format="cpu:%U" ./prog.exe "$i"
#  ./prog.exe "$i" >> test/partition.dat
#done
#
#make -BC test partition.png

./prog.exe
