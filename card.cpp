// This class represents a playing card, i.e., "ace of spades"
// a Card is constructed from a rank (int in range 1..13)
// and a suit (Card::spades, Card::hearts, Card::diamonds,
// Card::clubs)
//
// Cards should be created by a Deck (see deck.h), a Deck returns
// good cards
// The function toString() converts a card to a string, e.g., to print
//
// Accessor functions include
//
// int GetRank()      -- returns 1, 2, ..., 13 for ace, two, ..., king
//
// bool SameSuitAs(c) -- returns true if same suit as Card c
//
// string suitString() -- returns "s", "h", "d" or "c"
//
// Note that the Ace is represented by 1 and the King by 13
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include "card.h"


using namespace std;

Card::Card(){
    myRank = 1; // Rank of 1 means Ace
    mySuit = spades; // Default constructor is Ace of Spades
}
Card::Card(int rank, Suit s){
    myRank = rank;
    if(myRank == 0){
        cout << "ERROR" << endl;
    }
    mySuit = s;
}
//  string toString()              const;  // return string version e.g. Ac 4h Js
string Card::toString() const{
    string myString = rankString(myRank) + suitString(mySuit);
    return myString;
}
// string rankString(int r)       const;  // return "A", "2", ..."Q"

string Card::rankString(int r) const{
    string ans = "";
    if(r == 0){
        cout << "ERROR" << endl;
    }
    switch(r){
        case 1:
            ans = "A";
            break;
        case 11:
            ans = "J";
            break;
        case 12:
            ans = "Q";
            break;
        case 13:
            ans = "K";
            break;
        default:
            ans = to_string(r);
            break;
    }
    return ans;
}

// string suitString(Suit s)      const;  // return "s", "h",...
string Card::suitString(Suit s) const{

    switch(s){
        case 0:
            return "S";
            break;
        case 1:
            return "H";
            break;
        case 2:
            return "D";
            break;
        case 3:
            return  "C";
            break;
        default:
            return "C";
            break;
    }
}

// bool sameSuitAs(const Card& c) const;  // true if suit same as c
// int  getRank()                 const;  // return rank, 1..13
bool Card::sameSuitAs(const Card& c) const{
    if(suitString(mySuit) == c.suitString(c.mySuit)){
        return true;
    }
    else{
        return false;
    }
}

int Card::getRank() const{
    return myRank;
}

//  bool operator == (const Card& rhs) const;
// bool operator != (const Card& rhs) const;
bool Card::operator==(const Card& rhs) const{
    if(sameSuitAs(rhs) && (myRank == rhs.getRank())){
        return true;

    }
    else{
        return false;
    }
}
bool Card::operator!=(const Card& rhs) const{
    if(!sameSuitAs(rhs) || (myRank != rhs.getRank())){
        return true;
    }
    else{
        return false;
    }
}


ostream& operator << (ostream& out, const Card& c){
    string cardString  = c.toString();
    out << cardString;
    return out;
}
Card::Suit& operator++(Card::Suit& s){
    return s = (s == Card::clubs) ? Card::spades : static_cast<Card::Suit>(static_cast<int>(s) + 1);
}