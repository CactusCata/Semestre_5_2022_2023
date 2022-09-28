CC=g++
CFLAGS=-Wall
SRC_DIR=src
SRC=$(wildcard $(SRC_DIR)/*.cpp)
OBJ:=$(patsubst $(SRC_DIR)/%.cpp,%.o,$(SRC))

# Build .exe executable
program.exe: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Build .o objects
%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

# Build cleaner
clean:
	rm -f *.o *.exe *~
