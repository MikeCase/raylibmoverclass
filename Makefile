all:
	g++ -o ./bin/mover main.cpp mover.cpp Player.cpp -lraylib

mover:
	g++ -o ./bin/mover main.cpp mover.cpp Player.cpp -lraylib
