set term png
set output 'partition.png'
set title 'comparaison de n et time(P(n))'
set xlabel 'n'
plot 'partition.dat'
quit
