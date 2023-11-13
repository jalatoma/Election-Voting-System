#ifndef _IRVBALLOT_H
#define _IRVBALLOT_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "candidate.h"
#include "IRVCandidate.h"

using namespace std;

/**
 * @brief This is the ballot parser for IRV elections
 */
class IRVBallot {
    private:
        // queue<int> rank;
        // vector<Candidate> candidates;
        int numBallots;

    public:
        /**
         * @brief Defualt constructor for the IRVBallot class
         */
        IRVBallot();

        /**
         * @brief Gets the count of ballots
         * @return Int amount of how mnay ballots there are 
         */
        int getCount();

        /**
         * @brief Pushes the candidates onto another class
         * @param IRVCandidate This is the object we want to push onto
         */
        void pushCandidates(IRVCandidate* x);
        // IRVCandidate* pop();

        /**
         * @brief Checks to see if there are any ballots
         * @return Boolean if yes or no empty
         */
        bool isempty();

        /**
         * @brief Sets the number of ballots
         * @param int This is the number of ballots we want to set it to
         */
        void setnumBallots(int count);

        /**
         * @brief Gets the number of ballots in the election
         * @return Int value of the ballots in the election
         */
        int getnumBallots();

        /**
         * @brief Holds the candidates for the election
         */
        vector<IRVCandidate*> candidates;

        /**
         * @brief Holds the ballots in a vector
         */
        vector<vector<int>> ballotsVector;
};

#endif
