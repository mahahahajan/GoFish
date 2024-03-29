// FILE: card_demo.cpp
// This is a small demonstration program showing how the Card and Deck classes
// are used.
#include <fstream>
#include <cstdlib>   // Provides EXIT_SUCCESS
#include <iostream>  // Provides outputFileand cin

#include "card.h"
#include "deck.h"
#include "player.h"

using namespace std;

vector<Player *> myPlayers;

// PROTOTYPES for functions used by this demonstration program:
void dealHand(Deck &d, Player &p, int numCards);
void showGameState(int turnCount, int playerCount, int &bookCount);
void nextTurn(Card &c1, Card &c2, Deck &d);
void firstTurn(Card &c1, Card &c2);

ofstream outputFile;

int main() {
    int playerCount = 0;
    int numCardsPerPlayer = 5;
    int bookNumber = 0;
    int turnCount = 0;
    Card c1;
    Card c2;

    
    outputFile.open ("gofish_results.txt");
    
    for (int i = 1; i < 3; i++) {  // For a 2 player game
        Player *p1 = new Player(("Player " + to_string(i)));
        myPlayers.push_back(p1);
        playerCount++;
       
    }
    // //Player 1
    // Player p1("Player 1");
    // playerCount++;

    // //Player 2
    // Player p2("Player 2");
    // playerCount++;

    // Player 3
    // Player p3("Player 3");
    // playerCount++;

    if (playerCount < 3) {
        numCardsPerPlayer = 7;
    } else {
        numCardsPerPlayer = 5;
    }

    Deck d;  // create a deck of cards
    d.shuffle();

    for (int i = 0; i < myPlayers.size(); i++) {
        dealHand(d, *(myPlayers.at(i)), numCardsPerPlayer);
    }

    showGameState(turnCount, playerCount, bookNumber);
    firstTurn(c1, c2);
    turnCount++;

    showGameState(turnCount, playerCount, bookNumber);

    while (bookNumber < 26) {
        //        outputFile<< "Number of books is : " << bookNumber << "\n" << endl;
        bookNumber = 0;
        nextTurn(c1, c2, d);
        showGameState(turnCount, playerCount, bookNumber);
    }
    int max = 0;
    int numberOfPlayer = 0;
    for (int i = 0; i < myPlayers.size(); i++) {
        Player *currPlayer = myPlayers.at(i);
        if (((currPlayer->getBookSize()) / 2) > max) {
            max = (currPlayer->getBookSize()) / 2;
            numberOfPlayer = i;
        }
    }
    outputFile<< myPlayers.at(numberOfPlayer)->getName() << " wins!" << endl;
    outputFile.close();

    myPlayers.clear();

    // dealHand(d, p3, numCardsPerPlayer);

    // outputFile<< p1.getName() << " has: " << p1.showHand() << endl;
    // outputFile<< p2.getName() << " has: " << p2.showHand() << endl;

    // p1.checkHandForBook(c1, c2);
    // p2.checkHandForBook(c1, c2);

    // outputFile<< p1.getName() << " now has: " << p1.showHand() << endl;
    // outputFile<< p2.getName() << " now has: " << p2.showHand() << endl;
    // Player 1 goes first

    return EXIT_SUCCESS;
}

void dealHand(Deck &d, Player &p, int numCards) {
    for (int i = 0; i < numCards; i++) {
        p.addCard(d.dealCard());
    }
}

void showGameState(int turnCount, int playerCount, int &bookCount) {
    if (turnCount == 0) {
        outputFile<< "Game Started with " << playerCount << " players" << endl;
        outputFile<< "\n";  // dont need to flush the output, only need a new line
        outputFile<< "Cards have been dealt" << endl;
    }

    outputFile<< "***************************************" << endl;
    outputFile<< "Current Hands: " << endl;
    outputFile<< "***************************************" << endl;

    for (int i = 0; i < myPlayers.size(); i++) {
        Player *currPlayer = myPlayers.at(i);
        outputFile<< currPlayer->getName() << " has: " << currPlayer->showHand()
             << endl;
        //        myPlayers.at(i) = &currPlayer;
    }
    outputFile<< endl;
    if (turnCount > 0) {
        outputFile<< "***************************************" << endl;
        outputFile<< "Current Books: " << endl;
        outputFile<< "***************************************" << endl;
        for (int i = 0; i < myPlayers.size(); i++) {
            Player *currPlayer = myPlayers.at(i);
            outputFile<< currPlayer->getName() << " has: \n"
                 << currPlayer->showBooks() << endl;
            bookCount += (currPlayer->getBookSize()) / 2;
        }
        outputFile<< endl;
    }
}
void firstTurn(Card &c1, Card &c2) {
    outputFile<< "The opening gambit: The first books of the game are made" << endl;
    outputFile<< endl;
    for (int i = 0; i < myPlayers.size(); i++) {
        Player *currPlayer = myPlayers.at(i);
        currPlayer->checkHandForBook(c1, c2);
    }
}
void nextTurn(Card &c1, Card &c2, Deck &d) {
    int flag = 0;
    for (int i = 0; i < myPlayers.size(); i++) {
        Player *currPlayer = myPlayers.at(i);
        int nextPlayerNum = i + 1;
        if (nextPlayerNum >= myPlayers.size()) {
            nextPlayerNum = 0;
        }
        Player *nextPlayer = myPlayers.at(nextPlayerNum);

        Card c = currPlayer->chooseCardFromHand();
        int cardRank = c.getRank();
        if(cardRank != 100){
            outputFile<< currPlayer->getName() << " asks - Do you have any "
                 << c.rankString(cardRank) << endl;
        }


        while (nextPlayer->sameRankInHand(c)) {
            outputFile<< nextPlayer->getName() << " says - Yes. I have a "
                 << c.rankString(cardRank) << endl;
            
            Card removeCard = nextPlayer->removeCardFromHand(c);
            currPlayer->addCard(removeCard);
            currPlayer->checkHandForBook(c1, c2);

            // LOGIC HERE
            if(currPlayer-> getHandSize() > 0){
                c = currPlayer->chooseCardFromHand();
                cardRank = c.getRank();
                outputFile<< currPlayer->getName() << " asks - Do you have any "
                         << c.rankString(cardRank) << endl;

            }
            else{
                flag++;
            }

        }

        outputFile<< nextPlayer->getName() << " says - Go Fish \n" << endl;

        if(d.size() > 0){
            Card newCard = d.dealCard();
            while(newCard.getRank() > 13 || newCard.getRank() < 1) {
                outputFile<< "ERROR: for some reason this isn't working" << endl;
                newCard = Card(14, Card::Suit(0));
            }
            if(!currPlayer->cardInHand(newCard) && !nextPlayer -> cardInHand(newCard) && newCard.getRank() != 14){ //Basically this card shouldn't be on the board anywhere rn
                currPlayer->addCard(newCard);
            }

            currPlayer->checkHandForBook(c1, c2);
        }



    }
}