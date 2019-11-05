final: card_demo.o card.o deck.o player.o
	g++ +g -otest card_demo.o card.o deck.o player.o
# driver: UtPodDriver.cpp UtPod.h Song.h
# 	g++ +g -c UtPodDriver.cpp
# player.o: player.cpp player.h card.h deck.h
# 	g++  -c player.cpp	
# deck.o: deck.cpp deck.h card.h
# 	g++  -c deck.cpp
card.o: card.cpp card.h
	g++ -g -std=c++11 -c card.cpp