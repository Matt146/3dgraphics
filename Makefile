all:
	g++ Source.cpp Camera.cpp World.cpp `sdl2-config --cflags --libs`
	./a.out