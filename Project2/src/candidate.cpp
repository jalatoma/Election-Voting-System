#include "candidate.h"

Candidate::Candidate(){
    name = "";
    votes = 0;
    party = "";
}

Candidate::Candidate(string candidateName){
    name = candidateName;
    votes = 0;
    party = "";
}

int Candidate::getVotes(){
    return votes;
}
void Candidate::increaseVote() {
    votes++;
}

string Candidate::getName(){
    return name;
}

string Candidate::getParty(){
    return party;
}

void Candidate::setParty(string x) {
    party = x;
}

void Candidate::setName(string setName) {
    name = setName;
}