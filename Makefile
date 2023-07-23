all:
	g++ main.cpp Camera.cpp World.cpp Cube.cpp `sdl2-config --cflags --libs`
	./a.out