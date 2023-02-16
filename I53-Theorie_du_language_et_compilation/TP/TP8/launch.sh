clear
rm -f ./prog.exe

cd src
make clean
make

cd ../
$2 ./prog.exe $1
rm -f ./prog.exe

cd src
make clean
