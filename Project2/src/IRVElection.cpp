#include "IRVElection.h"
#include <string>

using namespace std;

int IRVElection::count = 0;

IRVElection::IRVElection(){
  count++;
}

Candidate* IRVElection::calcResults(string filename) {
    // opens the input file and creates the audit file for this election
    ifstream filein(filename);
    auditFile.setElectionType("IRV", count);
   
    string fileWrite = auditFile.getfileOutput();
    ofstream file = auditFile.OpenFile(fileWrite);

    invalidFile.setInvalidFile(count);
    string invalidFileWrite = invalidFile.getfileOutput();
    ofstream file2 = invalidFile.OpenFile(invalidFileWrite);
    // lots of code for the election here
    string line;
    getline(filein, line); // election type

    // writing to the audit file, this is seen throughout the code
    file << "Type of election: " << line << endl;

    getline(filein,line); // num candidates
    int numCandidates = stoi(line);
    setNumCandidates(numCandidates);

    file << "Number of Candidates: " << line << endl;

    getline(filein,line); // get candidates names
    stringstream candidatesLine(line);
    string tmp;
    IRVBallot* ballots = new IRVBallot();
    char comma = ',';
    file << "Candidates: " << endl;

    // getting the names of the candidates and storing them in objects
    while (getline(candidatesLine, tmp, comma)) {
      tmp.erase(0, tmp.find_first_not_of(" ")); // erasing extra spaces
      tmp.erase(tmp.find_last_not_of(" ") + 1);
      IRVCandidate* candidate = new IRVCandidate(tmp);
      candidate->setInElection(true);
      ballots->pushCandidates(candidate); // putting candidates into ballots
      file << tmp << endl;
    }

    getline(filein,line); // getting number of ballots
    int numBallots = stoi(line);
    int originalBallots = numBallots;
    setNumBallots(numBallots);
    file << "Number of Ballots: " << numBallots << endl;
    ballots->setnumBallots(numBallots);
    char commaNS = ',';
    int numValidBallots = numBallots;
    // reading each ballot individually and storing them into a ballots vector
    for(int i = 0; i < numBallots; i++) {
      getline(filein, line);
      stringstream ballot(line);
      vector<int> ballotVotes;
      double validCands = numCandidates;
      while(getline(ballot, tmp, commaNS)) {
        // this is if the ballot has no ranking for an individual, to set them to 0
        if(tmp.size() == 0){
          tmp = "0";
          validCands--;
        }
        ballotVotes.push_back(stoi(tmp));
      }
      if(ballotVotes.size() < numCandidates) {
          ballotVotes.push_back(0);
          validCands--;
      }
      if((validCands/numCandidates) >= .5) {
        ballots->ballotsVector.push_back(ballotVotes);
      }
      else {
        numValidBallots--;
        // cout << line << endl;
        file2 << line << endl;

      }
    }
    // adding votes to the exhausted votes pile
    exhaustedPile.push_back(numBallots-numValidBallots);
    exhaustedPileChange.push_back(numBallots-numValidBallots);
    numBallots = numValidBallots;
    setNumBallots(numBallots);
    ballots->setnumBallots(numBallots);
    int j;
    // counting the actual votes
    file << "Distribution of original votes: " << endl;
    for(j = 0; j < numBallots; j++) {
      for(int a = 0; a < numCandidates; a++){
        // distributing the votes to the candidates 
        if(ballots->ballotsVector[j][a] == 1){
          ballots->candidates[a]->votes += 1;
          file << ballots->candidates[a]->votes << " " << ballots->candidates[a]->getName() << endl;
        }
      }
    }
    
    // getting all the votes in a round
    vector<int> roundVotes;
    for(int n = 0; n < numCandidates; n++) {
      roundVotes.push_back(ballots->candidates[n]->votes);
    }
    votesPerRound.push_back(roundVotes);
    changeInVotes.push_back(roundVotes);

    bool winNotFound = true;

    // looking for the winner of the election
    while(winNotFound) {
      for(j = 0; j < numCandidates; j++) {

        // checks for a majority 
        if((ballots->candidates[j]->votes / numBallots) > 0.5) { // cant do equals to here bc of the possibility of a tie 
          Candidate* winner = ballots->candidates[j];
          winNotFound = false;
          file << "The Winner by majority is: " << winner->getName() << endl;
          file.close();
          cout << "Winner: " << winner->getName() << endl;
          cout << endl;
          printTable(ballots, numCandidates, originalBallots);
          return winner;
        }
      }

      // elminate a candidate and transfer of votes if least voted for
      rounds++;
      eliminateCandidate(ballots, numBallots, numCandidates, file);
    }

    // close the audit file
    file.close();
    return NULL;
}


void IRVElection::eliminateCandidate(IRVBallot* ballots, int numBallots, int numCandidates, ofstream &file) {
   // finding the candidate to eliminate 
    int leastVotes = 99999;
    int leastCandidate = -1;

    file << "No winner by majority, redistributing votes" << endl;
    vector<int> vals;
    //check for least voted for individual
    for (int i = 0; i < numCandidates; i++) {
      vals.push_back(0);
      if ((ballots->candidates[i]->getInElection() == true) && (ballots->candidates[i]->votes <= leastVotes)) {
        if(ballots->candidates[i]->votes == leastVotes) {
          // check for a tie between candidates
          Candidate* tmp = breakTie(ballots->candidates[leastCandidate], ballots->candidates[i]);
          if(tmp->getName().compare(ballots->candidates[i]->getName()) == 0) {
            leastVotes = ballots->candidates[i]->votes;
            leastCandidate = i;
          }
        }
        else {
          leastVotes = ballots->candidates[i]->votes;
          leastCandidate = i;
        }

      }
    }

    file << ballots->candidates[leastCandidate]->getName() << " has the least votes, redistributing the votes" << endl;
    ballots->candidates[leastCandidate]->setInElection(false);

    // redistributing the votes of an eliminated candidate
    int val = ballots->candidates[leastCandidate]->votes;
    int exhTemp = val;
    for(int x = 0; x < numBallots; x++) {
      if (ballots->ballotsVector[x][leastCandidate] == 1) {
        int nextCan = 2;
        int y = 0;
        // checking who to redistribute to 
        // if the second ranked candidate is already eliminated, move to 3rd ranked and so on
        while(nextCan <= numCandidates) {
          if(ballots->ballotsVector[x][y] == nextCan && ballots->candidates[y]->getInElection()==true) {
            vals[y] += 1;
            ballots->candidates[y]->votes += 1;
            ballots->candidates[leastCandidate]->votes -= 1;
            exhTemp--;
            file << "Vote redistributed to " << ballots->candidates[y]->getName() << endl; 
            break;
          }
          y++;
          if(y == numCandidates) {
            y = 0;
            nextCan++;
            // break;
          }

        }
      }
    }
    // updating the votes for this round for the output table
    exhaustedPile.push_back(exhaustedPile[rounds-1] + exhTemp);
    exhaustedPileChange.push_back(exhTemp);
    vector<int> roundVotes;
    vector<int> eliminatedVotes;
    file << "Distribution of new votes: " << endl;
    for(int a = 0; a < numCandidates; a++){
        file << ballots->candidates[a]->getName() << " has " << ballots->candidates[a]->votes << endl;
        roundVotes.push_back(ballots->candidates[a]->votes);
        if(ballots->candidates[a]->getInElection()==true){
          eliminatedVotes.push_back(vals[a]);
        }
        else{
          eliminatedVotes.push_back(0-val);
        }
    }
    ballots->candidates[leastCandidate]->votes =0;
    changeInVotes.push_back(eliminatedVotes);
    votesPerRound.push_back(roundVotes);

    // cout << ballots->candidates[0]->votes << " " << ballots->candidates[2]->votes << " " << ballots->candidates[3]->votes;
}

// this function is what is called to print the output table of the election results
void IRVElection::printTable(IRVBallot* ballots, int numCandidates, int numBallots) {
  int rows = numCandidates + 4;
  rounds++;
  int cols = 1 + rounds;
  // top row
  cout << setw(10) << "Candidates(Party):" << "\t";
  for(int i = 1; i < cols - 1; i++) {
    cout << setw(3) << "Round: " << i << "\t";
  }
  cout << endl;
  // votes of candidates
  for(int i = 0; i < numCandidates; i++) {
    cout << setw(10) << ballots->candidates[i]->getName() << "\t";
    for(int j = 0; j < cols-2; j++) {
      cout << setw(10) << votesPerRound[j][i] << " (" << changeInVotes[j][i] << ") " << "\t";
      if(votesPerRound[j][i] == 0) {
        break;
      }
    }
    cout << endl;
  }

  // row of exhausted votes
  cout << setw(10) << "Exhausted Pile" << "\t";
  for(int i = 0; i < cols - 2; i++){
    cout << setw(10) << exhaustedPile[i] << " (" << exhaustedPileChange[i] << ") " << "\t";
  }

  cout << endl;

  cout << setw(10) << "Totals" << "\t";
  cout << setw(10) << numBallots << " (+" << numBallots << ")" << "\t";



  cout << endl;
}

int IRVElection::getnumCandidates(){
  return numCandidates;
}

void IRVElection::setnumCandidates(int number){
  numCandidates = number;
}

