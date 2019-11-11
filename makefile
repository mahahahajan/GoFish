final: go_fish.o card.o deck.o player.o
	g++ -g -otest -std=c++11 go_fish.o card.o deck.o player.o
# driver: UtPodDriver.cpp UtPod.h Song.h
# 	g++ +g -c UtPodDriver.cpp
go_fish.o: go_fish.cpp player.h card.h deck.h
	g++ -g -c -std=c++11 go_fish.cpp

player.o: player.cpp player.h card.h deck.h
	g++  -g -c -std=c++11 player.cpp	
deck.o: deck.cpp deck.h card.h
	g++ -g -c -std=c++11 deck.cpp
card.o: card.cpp card.h
	g++ -g -std=c++11 -c card.cpp