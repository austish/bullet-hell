# Makefile

CXX_FLAGS = -lGL -lglut --std=c++11

all: main

main: main.cpp
	g++ $(CXX_FLAGS) -o main main.cpp -I/opt/homebrew/include -L/opt/homebrew/lib lib/player.cpp lib/npc.cpp

clean:
	rm -f *.o main