all: main

main: mohr.o stressys.o src/stressys.h gtk
	g++ src/mohr.o src/stressys.o -o mohr

mohr.o: src/mohr.cpp
	g++ -c src/mohr.cpp -o src/mohr.o

stressys.o: src/stressys.cpp
	g++ -c src/stressys.cpp -o src/stressys.o

clean:
	rm -rf src/*o mohr gmohr

gtk: stressys.o 
	g++ -Wall src/stressys.o  src/gtk_mohr.cpp -o gmohr `pkg-config --cflags --libs gtk+-2.0`
