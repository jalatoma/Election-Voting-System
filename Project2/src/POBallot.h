#ifndef _POBALLOT_H
#define _POBALLOT_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "candidate.h"

using namespace std;

/**
* @brief This is the populatory only ballot class
*/
class POBallot {
    private:
        int numBallots;
    
    public:
        /**
        * @brief This is the constructor for the class
        */
        POBallot();

        /**
        * @brief This gets the number of ballots
        * @return An int of the nyumber of ballots
        */
        int getNumBallots();

        /**
        * @brief This sets the number of ballots
        */
        void setNumBallots(int count);

        /**
        * @brief This pushes the candidates onto a vector
        */
        void pushCandidates(Candidate* x);
        
        // these vectors hold the candidates for the election and the ballots
        vector<Candidate*> candidates;
        vector<vector<int>> ballotsVector;
};

#endif