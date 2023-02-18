# This is an example make file

CXX = g++  # the compiler
CXXFLAGS = -std=c++20 -Wall -g  # flags for the compiler (use c++20 standards, turn on all optional warnings); add -ggdb if you want to use gdb to debug!

# runs for "make all"
all: main test

#runs for make test
test: Player.o Game.o test.cpp
	$(CXX) $(CXXFLAGS) test.cpp Player.o Game.o -o test # name of output should be consistent

# runs for "make main"
main: Player.o Game.o main.cpp
	$(CXX) $(CXXFLAGS) main.cpp Player.o Game.o -o main # name of output should be consistent

Player.o: Player.cpp
	$(CXX) $(CXXFLAGS) -c Player.cpp

Game.o: Game.cpp
	$(CXX) $(CXXFLAGS) -c Game.cpp

# runs for "make clean"
clean:
	rm Player.o Game.o main test #include all targets here
