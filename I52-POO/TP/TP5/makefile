CC = g++
CFLAGS = -g -Wall

program.exe: main.o etudiant.o personne.o cursus.o professeur.o matiere.o administration.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	clear
	rm -f *.exe *.o
