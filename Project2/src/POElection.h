#ifndef _POELECTION_H
#define _POELECTION_H

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <list>
#include <algorithm>
#include <cmath>
#include "audit.h"
#include "election.h"
#include "POBallot.h"
#include "candidate.h"
using namespace std;

/**
* @brief This is the popularity only election class
*/
class POElection : public Election {
    private:
        int numCandidates;
        Audit auditFile;
        Audit invalidFile;

    public:
        /**
        * @brief This is the constructor
        */
        POElection();

        /**
        * @brief This gets the number of candidates
        * @return the int of number of candidates
        */
        int getNumCandidates();

        /**
        * @brief This sets the number of candidates
        */
        void setNumCandidates(int number);

        /**
        * @brief This calculates the results of the election
        * @return The winner of type Candidate class
        */
        Candidate* calcResults(string filename);

        // this is for the audit file naming convention
        static int count;
};

#endif