#include <iostream>
#include <string>
#include <fstream>
#include "election.h"
#include "IRVElection.h"
#include "candidate.h"
#include "CPLElection.h"
#include "POElection.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]){

    string filename;

    if(argc < 2){
        cout << "Not enough arguments\n";
        return 1;
    }
    Election* test = new Election();
    if(argc == 2) {
        filename = argv[1];
    }
    else {
        for (int i = 1;i < argc;i++) {
            test->combine(argv[i],i-1);
        }
        filename = "../testing/final.csv";

    }
        // cout << "filename " << filename << endl;

        Election* election = new Election(filename);
        string electiontype = election->getElectionType();
        if(strcmp(electiontype.c_str(), "IR") == 0){
            IRVElection* testElec1 = new IRVElection();
            testElec1->calcResults(filename);
        } else if (strcmp(electiontype.c_str(), "CPL") == 0){
            CPLElection* testElec = new CPLElection();
            testElec->calcResults(filename);
            
        } 
        else if (strcmp(electiontype.c_str(), "PO") == 0){
            POElection* testElec = new POElection();
            testElec->calcResults(filename);
        }else {
            cout << filename << " is invalid\n" << endl;
        }
    
}
