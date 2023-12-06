# Makefile

CXX_FLAGS = --std=c++11
LIBS = -lGL -lglut

all: main

main: main.cpp
<<<<<<< Updated upstream
	g++ $(CXX_FLAGS) -o main main.cpp -I/opt/homebrew/include -L/opt/homebrew/lib lib/player.cpp lib/npc.cpp
=======
	g++ $(CXX_FLAGS) -o main main.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -Ilib lib/player.cpp lib/npc.cpp lib/bullet.cpp lib/borders.cpp lib/ui.cpp lib/menu.cpp $(LIBS)
>>>>>>> Stashed changes

clean:
	rm -f *.o main
