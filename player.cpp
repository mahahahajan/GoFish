// FILE:  player.h
// written by Roger Priebe
// 1/22/08 (revised 9/2/08)
// This class represents a player in a card game that takes "tricks"
// The "Books" represent a container for holding tricks

#include "player.h"

using namespace std;

Player::Player() { myName = "Pulkit/Sylvia"; }

void Player::addCard(Card c) { myHand.push_back(c); }

bool Player::checkHandForBook(Card &c1, Card &c2) {
    int flag = 0;
    int breakNum = 0;
    for (int i = 0; i < myHand.size(); i++) {
        Card c = myHand.at(i);
        breakNum = 0;
        for (int j = 0; j < myHand.size(); j++) {
            if(breakNum != 0){
               c = Card(100, Card::Suit(0));
               j = 0;
            }
            if ( (myHand.at(j).getRank() == c.getRank() ) && (myHand.at(j) != c)) {  // same Rank, diff card
                    bookCards(myHand.at(j), c);  // book cards
                    // Remove cards
                    removeCardFromHand(myHand.at(j));
                    removeCardFromHand(c);
                    //Made a pair so lets reset everything
                    breakNum = 10;
                    flag++;
                    i = 0;
                }
            }


    }
    if(flag > 0){
        return true;
    }
    else{
        return false;
    }
}

void Player::bookCards(Card c1, Card c2) {
    myBook.push_back(c1);
    myBook.push_back(c2);
}

Card Player::chooseCardFromHand() const {
    srand(time(0));
    if(myHand.size() > 0){
        int randomNum = rand() % myHand.size();
        for (int i = 0; i < myHand.size(); i++) {
            if (i == randomNum) {
                return myHand.at(i);
            }
        }
        return myHand.at(5);
    }
    return Card(100, Card::Suit(3));

}

bool Player::cardInHand(Card c) const {
    for (int i = 0; i < myHand.size(); i++) {
        if (myHand.at(i) == c) {

                return true;

        }
    }
    return false;
}

Card Player::removeCardFromHand(Card c) {
    Card returnCard;
    for (int i = 0; i < myHand.size(); i++) {
        if (myHand.at(i).getRank() == c.getRank()) {
            returnCard = myHand.at(i);
            myHand.erase(myHand.begin() + i);

        }
    }
    return returnCard;
}

string Player::showHand() const {
    string myCards = "";
    for (int i = 0; i < myHand.size(); i++) {
        myCards += myHand.at(i).toString();
        myCards += "    ";
    }
    return myCards;
}

string Player::showBooks() const {
    string myBooksString = "";
    if (myBook.size() > 0) {
        myBooksString = "\t Book 1: ";
        for (int i = 0; i < myBook.size(); i++) {
            if (i % 2 == 0 && i != 0) {
                myBooksString += "\n ";
                myBooksString += "\t Book " + to_string((i / 2 + 1)) + ": ";
            }
            myBooksString += myBook.at(i).toString();
            myBooksString += "   ";

        }
    }
    return myBooksString;
}

int Player::getHandSize() const { return myHand.size(); }
int Player::getBookSize() const { return myBook.size(); }
bool Player::sameRankInHand(Card c) const {
    for (int i = 0; i < myHand.size(); i++) {
        if (myHand.at(i).getRank() == c.getRank()) {
            if (myHand.at(i) != c) {
                return true;
            }
        }
    }
    return false;
}