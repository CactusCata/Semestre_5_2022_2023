clear

cd lib
make clean
make libgraph.a

cd ../test
make clean
make prog.exe

./prog.exe
