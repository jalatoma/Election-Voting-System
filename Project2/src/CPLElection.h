#ifndef _CPLELECTION_H
#define _CPLELECTION_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <list>
#include <algorithm>
#include <iterator>
#include "CPLCandidate.h"
#include "party.h"
#include "audit.h"
#include "election.h"

using namespace std;

/**
 * @brief This is the CPL election river class
 */
class CPLElection : public Election{
    private:
        int numCandidates;
        Audit auditFile;

    public:
        /**
         * @brief This is the default constructor
         */
        CPLElection();

        /**
         * @brief This runs the main CPL election
         * @param string Input file with the ballots 
         */
        Party* calcResults(string filename);

        /**
         * @brief Sets the vector of all the parties
         */
        vector<Party*> parties;

        /**
         * @brief Gets the number of candidates
         * @return Int of number of candidates
         */
        int getnumCandidates();

        /**
         * @brief Sets the number of candidates
         * @param int The number of candidates we want to set it to
         */
        void setnumCandidates(int number);

        // this sets the count for the audit files
        static int count;
};

#endif