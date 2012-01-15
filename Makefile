all: main

main: mohr.o stressys.o src/stressys.h gtk
	g++ src/mohr.o src/stressys.o -o mohr

mohr.o: src/mohr.cpp
	g++ -c src/mohr.cpp -o src/mohr.o

stressys.o: src/stressys.cpp
	g++ -c src/stressys.cpp -o src/stressys.o

gtk: stressys.o 
	g++ -Wall src/stressys.o  src/gtk_mohr.cpp -o gmohr `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm -rf src/*o mohr gmohr

install:
	mkdir /usr/local/gmohr
	cp ./mohr /usr/local/gmohr/
	cp ./gmohr /usr/local/gmohr/
	ln -s -T /usr/local/gmohr/gmohr /usr/local/bin/gmohr
	ln -s -T /usr/local/gmohr/mohr /usr/local/bin/mohr

uninstall:
	rm -rf /usr/local/gmohr
	rm /usr/local/bin/mohr
	rm /usr/local/bin/gmohr

