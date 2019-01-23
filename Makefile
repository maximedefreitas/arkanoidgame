main: delete main.cpp
	mkdir obj
	mkdir obj/Debug
	mkdir obj/Debug/src
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c main.cpp -o obj/Debug/main.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/ball.cpp -o obj/Debug/src/ball.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/bonus.cpp -o obj/Debug/src/bonus.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/brick.cpp -o obj/Debug/src/brick.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/bricka.cpp -o obj/Debug/src/bricka.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/brickb.cpp -o obj/Debug/src/brickb.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/brickc.cpp -o obj/Debug/src/brickc.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/brickd.cpp -o obj/Debug/src/brickd.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/bricko.cpp -o obj/Debug/src/bricko.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/brickp.cpp -o obj/Debug/src/brickp.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/brickr.cpp -o obj/Debug/src/brickr.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/brickg.cpp -o obj/Debug/src/brickg.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/brickw.cpp -o obj/Debug/src/brickw.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/bricky.cpp -o obj/Debug/src/bricky.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/explosion.cpp -o obj/Debug/src/explosion.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/game.cpp -o obj/Debug/src/game.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/hitbox.cpp -o obj/Debug/src/hitbox.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/laser_beam.cpp -o obj/Debug/src/laser_beam.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/terrain.cpp -o obj/Debug/src/terrain.o
	g++ -Wall -fexceptions -g -std=c++14 -pg -Iinclude -c src/vaisseau.cpp -o obj/Debug/src/vaisseau.o
	g++  -o Arkanoid obj/Debug/main.o obj/Debug/src/ball.o obj/Debug/src/bonus.o obj/Debug/src/brick.o obj/Debug/src/bricka.o obj/Debug/src/brickb.o obj/Debug/src/brickc.o obj/Debug/src/brickd.o obj/Debug/src/bricko.o obj/Debug/src/brickp.o obj/Debug/src/brickr.o obj/Debug/src/brickg.o obj/Debug/src/brickw.o obj/Debug/src/bricky.o obj/Debug/src/explosion.o obj/Debug/src/game.o obj/Debug/src/hitbox.o obj/Debug/src/laser_beam.o obj/Debug/src/terrain.o obj/Debug/src/vaisseau.o  -pg  -lSDL2

delete:
	rm -rf Arkanoid
	rm -rf obj

