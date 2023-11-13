#include "IRVCandidate.h"

IRVCandidate::IRVCandidate(std::string name) : Candidate(name) {}

bool IRVCandidate::getInElection(){
  return inElection;
}

// void IRVCandidate::eliminate(string name){
//   // delete from candidates queue? and update inElection variable of candidate
//   eliminated.push_back(name);
// }

void IRVCandidate::setInElection(bool in) {
  inElection = in;
}
