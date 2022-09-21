SHELL=/bin/bash
#CC=gcc
#FLAGS=-g -Wall

# Question 1
crible: crible.c
	gcc crible.c -o crible.exe

# Question 2
# Le paramètre -l permet de dire jusqu'à
# quelle valeur en puissance de deux l'algorithme
# va chercher.
#
# Le paramètre -p correspond au nombre
# de print (notion de pas)
data.dat: crible.exe
	./crible.exe -p100 -l10 | sed "s/pi(//g" | sed "s/)/ /g" >> data.dat

#./crible.exe -p100 -l10 > tmp; cat tmp | sed "s/pi(//g" | sed "s/)=/ /g" > data.dat

# Question 3
#
# Produit un fichier pi.png
#
pi.png: data.dat data.plot
	gnuplot data.plot

# Question 4
timing.png: crible
	> timing.dat
	for i in {10..28}; \
	do \
		./crible -t -l $$i >> timing.dat \
	done
	gnuplot timing.plot

# Question 5
criblesOX.exe: crible.c
	gcc -g -Wall -O1 ./crible.c -o cribleO1.exe
	gcc -g -Wall -O2 ./crible.c -o cribleO2.exe
	gcc -g -Wall -O3 ./crible.c -o cribleO3.exe

timingOx.png: criblesOX.exe timing.dat
	touch timingO1.dat
	rm timingO1.dat
	touch timingO1.dat

	touch timingO2.dat
	rm timingO2.dat
	touch timingO2.dat

	touch timingO3.dat
	rm timingO3.dat
	touch timingO3.dat

	for i in {10..28}
	do
		./cribleO1.exe $$i > timingO1.dat
		./cribleO2.exe $$i > timingO2.dat
		./cribleO3.exe $$i > timingO3.dat
	done
	gnuplot timingOx.plot

# Question 6
compterendu: compte_rendu.tex pi.png timing.png timingOx.png
	pdflatex compte_rendu.tex
