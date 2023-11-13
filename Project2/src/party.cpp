#include "party.h"

// default constructor
Party::Party(){
    partyName = "";
    votes = 0;
    seats = 0;
}

// other constructor with name
Party::Party(string name) {
    partyName = name;
    votes = 0;
    seats = 0;
}

// getters
string Party::getPartyName() {
    return partyName;
}

int Party::getPartyVotes() {
    return votes;
}

int Party::getPartySeats() {
    return seats;
}

int Party::getRemainingVotes() {
    return remainingVotes;
}

//setters
void Party::setPartyName(string name) {
    partyName = name;
}

void Party::setPartyVotes(int partyVotes) {
    votes = partyVotes;
}

void Party::setPartySeats(int partySeats) {
    seats = partySeats;
}

void Party::setRemainingVotes(int votes) {
    remainingVotes = votes;
}

void Party::incrementVotes() {
    votes++;
}