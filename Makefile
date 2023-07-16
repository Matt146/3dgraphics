all:
	g++ Source.cpp Camera.cpp `sdl2-config --cflags --libs`
	./a.out