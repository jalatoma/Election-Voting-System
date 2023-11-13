#include "CPLCandidate.h"

//default constructor
CPLCandidate::CPLCandidate(){}

// constructor
CPLCandidate::CPLCandidate(std::string name) : Candidate(name) {}

int CPLCandidate::getPartyRank(){
    return partyRank;
}

void CPLCandidate::setPartyRank(int rank) {
    partyRank = rank;
}