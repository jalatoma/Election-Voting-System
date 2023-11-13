#include "IRVBallot.h"

IRVBallot::IRVBallot(){}

int IRVBallot::getCount(){ //gets count of number of candidates
    return candidates.size();
}

void IRVBallot::pushCandidates(IRVCandidate* x){
    candidates.push_back(x);
} // push ballot onto the array of candidates

// IRVCandidate* IRVBallot::pop(){
//    IRVCandidate* candidate = candidates.back();
//    candidates.pop_back();
//    return candidate;
// } // pop the ballot from the vector of candidates
bool IRVBallot::isempty() {
    return candidates.empty();
}

void IRVBallot::setnumBallots(int count) {
  numBallots = count;
}

int IRVBallot::getnumBallots(){
    return numBallots;
}


