#include "election.h"

Election::Election(){
    srand(time(NULL));
    numBallots = 0;

}
Election::Election(const string& filename){
    srand(time(NULL));
    // reads the input CSV file
    ifstream inputFile(filename);
    string line;
    getline(inputFile,line);
    // cout << line;
    electionType = line;
    file = filename;
    numBallots = 0;
}

int Election::getnumCand(){
    return numCand;
}

int Election::getnumBallots(){
    return numBallots;
}

int Election::getnumSeats(){
    return numSeats;
}

string Election::getElectionType(){

    return electionType;
}

void Election::getAdditionalInfo(){
    
}

void Election::setNumCandidates(int cands) {
    numCand = cands;
}

void Election::setNumBallots(int ballots) {
    numBallots = ballots;
}

void Election::setnumSeats(int seats){
    numSeats = seats;
}

void Election::increaseBallots(int x) {
    numBallots += x;
}
int Election::breakTie(int party1, int party2) {
  
    for (int i = 0;i<10000;i++) {
        rand();
    }
    if (rand()%2 == 0) {
        return party1;
    }
    else {
        return party2;
    }
}
Candidate* Election::breakTie(Candidate* cand1, Candidate* cand2) {
    for (int i = 0;i<10000;i++) {
        rand();
    }
    if (rand()%2 == 0) {
        return cand1;
    }
    else {
        return cand2;
    }
}

void Election::combine(string filename,int count) {

    ifstream filein(filename);
    cout << filename << endl;
    string line;
    string type;
    string additonalCPLheaders; // need to keep track of number of lines for CPL candidates
    stringstream currInfo;
   
    getline(filein,type);
    getline(filein,additonalCPLheaders);

    filein.clear(); 
    filein.seekg(0); // returns to beginning of file

    if(count == 0) { // puts headers only in if first file input
        if(type == "IR" || type == "PO") { //IRV
            headers = 3;
            
        }
        else if(type == "CPL") { //CPL
            headers = 4 + stoi(additonalCPLheaders);
        }
        else {
            cout << "invalid file\n" << endl;
            exit(1);
        }
        for(int i = 0;i<headers;i++) {// 
            getline(filein,line);
            currInfo << line << endl;
        }
    }
    else { // if not first file compare to first file
        ifstream x("../testing/final.csv");
        for(int i =0 ;i<headers;i++) {
            string lineFromFinal;
            getline(x,lineFromFinal);
            getline(filein,line);
            if(line != lineFromFinal) {
                cout << "wrong, Different types of elections" << endl;
                cout << lineFromFinal << endl;
                cout << line << endl;
                exit(1);
            }
            currInfo << line << endl;
        }
    }
    // cout << "headers " << headers << endl;
    getline(filein,line);
    increaseBallots(stoi(line)); // keep track of total number of ballots
    int numballots = (stoi(line)); 
    currInfo << getnumBallots() << endl;

    for(int i =0;i<numballots;i++) {
        getline(filein,line);
        ballots << line << endl;
    }
    // write everything to final every loop
    finalFile.open("../testing/final.csv");
    finalFile << currInfo.str();
    // cout << currInfo.str();
    finalFile << ballots.str();
    finalFile.close();
}