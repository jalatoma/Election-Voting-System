#ifndef _IRVCANDIDATE_H
#define _IRVCANDIDATE_H

#include <iostream>
#include <string>
#include <vector>
#include "candidate.h"
using namespace std;

/**
 * @brief Holds IRV candidates that inherits from candidate class
 */

class IRVCandidate : public Candidate {
    private:
        bool inElection;
        //vector<string> eliminated;
        //void eliminate(string name);
    public:
        /**
         * @brief This is the default constructor
         */
        IRVCandidate(){};

        /**
         * @brief This constructor sets the name of the candidate
         * @param string This is the name of the candidate
         */
        IRVCandidate(string name);

        /**
         * @brief This ets whether a candidate is still in the election or not (eliminated)
         * @return A boolean for true or false if in election
         */
        bool getInElection();

        /**
         * @brief This sets a candidate in an election with a boolean
         * @param bool This is the value if they are in or out of the election
         */
        void setInElection(bool in);

};
#endif
