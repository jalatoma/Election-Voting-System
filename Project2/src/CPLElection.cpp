#include "CPLElection.h"

using namespace std;

int CPLElection::count = 0;

CPLElection::CPLElection(){
    count++;
}

Party* CPLElection::calcResults(string filename){
    // opens the input file and the audit file
    ifstream filein(filename);
    auditFile.setElectionType("CPL", count);
    string fileWrite = auditFile.getfileOutput();
    ofstream file = auditFile.OpenFile(fileWrite);
    
    string line;
    getline(filein, line); // get election type

    // write to the audit file, this is seen throughout the code
    file << "Type of election: " << line << endl;

    getline(filein,line); // get num parties
    int numParties = stoi(line);
    file << "number of parties: " << numParties << endl;


    getline(filein,line); // get parties names
    stringstream partiesLine(line);
    string tmp;
    int index = 0;
    char comma = ',';
    file << "Parties: " << line << endl;

    // storing the parties into a vector
    while (getline(partiesLine, tmp, comma)) {
        tmp.erase(0, tmp.find_first_not_of(" ")); // erasing extra spaces 
        tmp.erase(tmp.find_last_not_of(" ") + 1);
        Party* party = new Party(tmp);
        parties.push_back(party);
    }

    file << "Candidates in each party: " << endl;

    // loop through each party to add candidates and their rank
    for (int i = 0; i < numParties; i++) {
        getline(filein, line); // candidates in party
        stringstream candidates(line);
        int rankCount = 1;
        file << parties[i]->getPartyName() <<": "<< endl;
        while(getline(candidates, tmp, comma)){
            CPLCandidate* cand = new CPLCandidate(tmp); // create a new candidate
            cand->setPartyRank(rankCount); 
            parties[i]->candidates.push_back(cand); // add candidate to parties vector
            file << tmp << " ";
        }
        file << endl;
    }
    file << endl;
    getline(filein, line); // number of seats
    int numSeats = stoi(line);
    file << "Number of seats: " << numSeats << endl;

    getline(filein, line); // ballots
    int numBallots = stoi(line);
    file << "Number of ballots: "<< numBallots << endl;

    file << "Couting the votes incrementally: " << endl;
    // count votes 
    for(int i = 0; i < numBallots; i++){
        getline(filein, line);
        stringstream ballot(line);
        int j = 0;
        // checks for first ranked party
        while(getline(ballot, tmp, comma)) {
            if(tmp.compare("1")==0){
                // increment the votes of first ranked
                parties[j]->incrementVotes();
                file << parties[j]->getPartyName() << " " << parties[j]->getPartyVotes() << endl;
                break;
            }
            j++;
        }
    }

    int quota = numBallots / numSeats; // this is integer division so we may have to change this to not have remainders
    int seatsAllocated=0;
    file << endl << "Quota for seats: " << quota << endl;

    file << "Allocating initial seats to each party: " << endl;
    // allocating seats
    for ( int i = 0; i < numParties; i++) {
        // cout << parties[i]->getPartyVotes() << endl;
        int initialSeats = parties[i]->getPartyVotes() / quota;
        // checking to make sure that there are enough candidates to fill all the seats they get
        if(initialSeats > parties[i]->candidates.size()) {
            initialSeats = parties[i]->candidates.size();
        }
        seatsAllocated += initialSeats;
        int remainder = parties[i]->getPartyVotes() % quota;
        parties[i]->setPartySeats(initialSeats); 
        // cout<<parties[i]->getPartyName()<<": "<<parties[i]->getPartySeats()<<endl;
        file << parties[i]->getPartyName()<<": "<<parties[i]->getPartySeats()<<endl;
        parties[i]->setRemainingVotes(remainder);
    }

    // get the amount of seats remaining
    int seatsRemaining = numSeats - seatsAllocated;
    vector<int> remainders;
    file << "Seats remaining: " << seatsRemaining << endl;
    file << "Remaining votes per party: " << endl;

    // get remaining votes of each party
    for(int j = 0; j < numParties; j++) {
        remainders.push_back(parties[j]->getRemainingVotes());
        file << parties[j]->getPartyName() << ": " << parties[j]->getRemainingVotes() << endl;

    }

    file << "Allocating reminder of seats: " << endl;
    // allocating remainder of seats. Only thing that is wrong is that this does not account for if 2 candidates are tied for the remaining seats
    for(int j = 0; j < seatsRemaining; j++) {
        int index = distance(remainders.begin(), max_element(remainders.begin(), remainders.end()));
        // int mostRemaining = *max_element(remainders.begin(), remainders.end());
        // int ind = -1;
        // for(int x = 0; x < numParties; x++) {
        //     if(parties[x]->getRemainingVotes() == mostRemaining) {
        //         if(ind != -1) {
        //             if(breakTie(ind, x) == x) {
        //                 parties[ind] = 0;
        //                 ind = x;
        //             }
        //             else {
        //                 parties[x] = 0;
        //             }
                    
        //         }
        //         else {
        //             ind = x;
        //         }
        //     }
        // }
        // cout << index <<endl;
        parties[index]->setPartySeats((parties[index]->getPartySeats()) + 1);
        remainders[index] = 0;
    }

    int winningPartyIndex = -1;
    int mostSeats = -1;
    // testing seat counts
    // figuring out which candidates get a vote
    for(int i = 0; i <numParties; i++) {
        // cout<<parties[i]->getPartyName()<<": "<<parties[i]->getPartySeats()<<endl;
        if(parties[i]->getPartySeats() > mostSeats) {
            mostSeats = parties[i]->getPartySeats();
            winningPartyIndex = i;
        }
        cout << "Party: " << parties[i]->getPartyName() << ". ";
        file << "Party: " << parties[i]->getPartyName() << ". ";
        for (int j = 0; j < parties[i]->getPartySeats(); j++) {
            parties[i]->candidates[j]->getsSeat = true;
            file << "Candidates that get seats: " <<  parties[i]->candidates[j]->getName()<< endl;
            cout << "Candidates that get seats: " <<  parties[i]->candidates[j]->getName()<< endl;
        } 

        // if no condidates in a party got seats, list that
        if (parties[i]->getPartySeats()==0){
            cout << "No candidates got seats." << endl;
            file << "No candidates got seats." << endl;
        }
        cout << endl;
    }
    return parties[winningPartyIndex];

}

int CPLElection::getnumCandidates(){
    return numCandidates;
}

void CPLElection::setnumCandidates(int number){
    numCandidates = number;
}