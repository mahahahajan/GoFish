// FILE: deck.h
// written by Owen Astrachan and Roger Priebe
// this class respresents a deck of cards
// When a Deck is constructed, it contains 52 cards
// in a "regular" order (aces, twos, threes, ... , kings)
//
// Shuffling a deck makes it consist of 52 cards in a random order
//
// dealCard() returns a card from the deck and decreases the
// number of cards in the deck (returned by size())
// The idea is that after shuffling, calling dealCard() 52 times
// returns each card in the deck after shuffling.
//
// Calling shuffle again replenishes the deck with 52 cards.

#include "deck.h"
using namespace std;

Deck::Deck(){
    myIndex = 0;
    int counter = 1;
    int suit = 0;

    for(int i = 0; i < 52; i++){
        if(i % 13 == 0 && i != 0){
            counter = 1;
            suit++;
            // ++s;
        }
        Card* myCard = new Card(counter, (Card::Suit) suit);
        myCards[i] = *myCard;
        counter++;
        delete myCard;
    }
}

// void shuffle();   // shuffle the deck, all 52 cards present
void Deck::shuffle(){

    srand((unsigned)time(0));

    int randomNum = rand() % 52;
    int index = 0;

    for(int i = 0; i < 52; i++){
//        index = i + randomNum;
//        if(index > 52){
//            index = i - randomNum;
//        }
        //Swap cards
        Card curr = myCards[i];
        myCards[i] = myCards[randomNum];
        myCards[randomNum] = curr;
        randomNum = rand() % 52;

    }

}
// Card dealCard();
Card Deck::dealCard(){
    Card curr = myCards[myIndex];

        myIndex++;

    return curr;
}
int Deck::size() const{
    return (52 - myIndex);
}

