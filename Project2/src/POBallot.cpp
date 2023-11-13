#include "POBallot.h"

POBallot::POBallot(){}

void POBallot::pushCandidates(Candidate* x) {
    candidates.push_back(x);
}

void POBallot::setNumBallots(int count) {
  numBallots = count;
}

int POBallot::getNumBallots(){
    return numBallots;
}