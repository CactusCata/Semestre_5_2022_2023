clear
rm -f ./prog.exe

cd src
make clean
make

cd ../
$3 ./prog.exe $1 $2
rm -f ./prog.exe

cd src
make clean
