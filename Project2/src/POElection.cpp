#include "POElection.h"
#include <string>

int POElection::count = 0;

// constructor
POElection::POElection(){
  count++;
}

int POElection::getNumCandidates(){
  return numCandidates;
}

void POElection::setNumCandidates(int number){
  numCandidates = number;
}

// function that calculates the results of the election
Candidate* POElection::calcResults(string filename) {
    ifstream filein(filename);

    auditFile.setElectionType("PO", count);
   
    string fileWrite = auditFile.getfileOutput();
    ofstream file = auditFile.OpenFile(fileWrite);
    
    string line;
    getline(filein, line); // election type
    // writing to the audit file, this is seen throughout the code
    file << "Type of election: " << line << endl;

    getline(filein, line); // num candidates
    int numCandidates = stoi(line);
    setNumCandidates(numCandidates);

    file << "Number of Candidates: " << line << endl;

    file << "Candidates: " << endl;

    getline(filein, line); // candidate names and party
    stringstream candidatesLine(line);
    string tmp;
    POBallot* ballots = new POBallot();
    char comma = ']'; 
    // getting all the candidates and adding them to the ballots
    while(getline(candidatesLine, tmp, comma)) {
        tmp.erase(0, tmp.find_first_not_of(" ")); // erasing extra spaces
        tmp.erase(tmp.find_last_not_of(" ") + 1);
        tmp.erase(remove(tmp.begin(), tmp.end(), '['), tmp.end());
        tmp.erase(0, tmp.find_first_not_of(","));
        tmp.erase(0, tmp.find_first_not_of(" "));
        Candidate* candidate = new Candidate(tmp);
        ballots->pushCandidates(candidate);
        file << tmp << endl;
    }

    getline(filein, line); // getting number of ballots
    int numBallots = stoi(line);
    setNumBallots(numBallots);
    ballots->setNumBallots(numBallots);
    file << "Number of Ballots: " << numBallots << endl;

    // counting votes
    char comma2 = ',';
    for(int i = 0 ; i < numBallots; i++) {
      getline(filein, line);
      stringstream ballot(line);
      int j = 0;
      // checks for ranked candidate
      while(getline(ballot, tmp, comma2)) {
        if(tmp.compare("1")==0){
          ballots->candidates[j]->votes++;
        }
        j++;
      }
    }

    int mostVotes = -1;
    int mostIndex = -1;
    // find winner !
    for(int j = 0; j < numCandidates; j++) {
      if(ballots->candidates[j]->votes >= mostVotes) {
        // check for ties
        if(ballots->candidates[j]->votes == mostVotes) {
          Candidate* tmp = breakTie(ballots->candidates[mostIndex], ballots->candidates[j]);
          if(tmp->getName().compare(ballots->candidates[j]->getName()) == 0) {
            mostVotes = ballots->candidates[j]->votes;
            mostIndex = j;
          }
        }
        else {
            mostVotes = ballots->candidates[j]->votes;
            mostIndex = j;
        }
      }
    }
    cout << endl;
    cout << "Most Votes: " << mostVotes << endl;
    cout << "Winner: " << ballots->candidates[mostIndex]->getName() << endl;
    cout << endl;

    file << "Most Votes: " << mostVotes << endl;
    file << "Winner: " << ballots->candidates[mostIndex]->getName() << endl;
    // printing out candidates and their respective votes
    for(int i = 0; i < numCandidates; i++) {
      double percent = round((ballots->candidates[i]->votes / (double) numBallots) * 100);
      cout << ballots->candidates[i]->getName() << " has " << ballots->candidates[i]->votes << " votes (" << percent << "%)." << endl;
      file << ballots->candidates[i]->getName() << " has " << ballots->candidates[i]->votes << " votes (" << percent << "%)." << endl;
    }
     // close the audit file
    file.close();
    return ballots->candidates[mostIndex];
}