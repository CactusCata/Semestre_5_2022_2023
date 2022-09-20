CC=g++
CFLAGS=-Wall

# Build .exe executables
exercice1.exe: mainExo1.o exo1.o libcomplexe.a
	$(CC) $(CFLAGS) mainExo1.o exo1.o -L. -lcomplexe -o $@

exercice2.exe: mainExo2.o libpolynome.a
	$(CC) $(CFLAGS) mainExo2.o -L. -lpolynome -o $@


# Build .o objects
complexe.o: complexe.cpp complexe.hpp
	$(CC) $(CFLAGS) -c $<

exo1.o: exo1.cpp exo1.hpp
	$(CC) $(CFLAGS) -c $<

polynome.o: polynome.cpp polynome.hpp
	$(CC) $(CFLAGS) -c $<

mainExo1.o: mainExo1.cpp mainExo1.hpp
	$(CC) $(CFLAGS) -c $<

mainExo2.o: mainExo2.cpp mainExo2.hpp
	$(CC) $(CFLAGS) -c $<


# Build .a libs
libcomplexe.a: complexe.o
	ar cr $@ $^
	ranlib $@

libpolynome.a: polynome.o
	ar cr $@ $^
	ranlib $@


# Cleaner
clean:
	rm -f *~ *.exe *.o *.a
