CC = g++
CFLAGS = -Wall


# Build executable .exe
program.exe: main.o personne.o etudiant1.o etudiant2.o professeur.o matiere.o
	$(CC) $(CFLAGS) -o $@ $^

# Build object .o
main.o: main.cpp main.hpp
	$(CC) $(CFLAGS) -c $<

personne.o: personne.cpp personne.hpp
	$(CC) $(CFLAGS) -c $<

etudiant1.o: etudiant1.cpp etudiant1.hpp
	$(CC) $(CFLAGS) -c $<

etudiant2.o: etudiant2.cpp etudiant2.hpp
	$(CC) $(CFLAGS) -c $<

matiere.o: matiere.cpp matiere.hpp
	$(CC) $(CFLAGS) -c $<

professeur.o: professeur.cpp professeur.hpp
	$(CC) $(CFLAGS) -c $<

clean:
	clear
	rm -f ~* *.exe *.o
