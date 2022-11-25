clear

cd lib
make clean
make

cd ../test
make clean
make prog.exe

cd ../
# Possible de mettre "valgrind" en lancant la commande:
# ./launch.sh valgrind
$1 ./prog.exe
