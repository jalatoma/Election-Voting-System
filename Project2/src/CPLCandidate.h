#ifndef _CPLCANDIDATE_H
#define _CPLCANDIDATE_H

#include <iostream>
#include <string>
#include "candidate.h"

/**
 * @brief This is the CPL candidates, which inherit from the Candidate class
 */
class CPLCandidate : public Candidate {
    private: 
        int partyRank;
    public:
        /**
         * @brief Constructor for the CPL candidates
         */
        CPLCandidate();

        /**
         * @brief Constructor that sets the name of the candidate
         * @param string This is the name we are setting the candidate to
         */
        CPLCandidate(std::string name);

        /**
         * @brief Sets the party rank of for CPL party
         * @param int This is the rank we want to set it to
         */
        void setPartyRank(int rank);

        /**
         * @brief Gets the rank of the speicified party
         * @return An int of the party rank
         */
        int getPartyRank();

        /**
         * @brief bBolean of if a party or candidate gets a seat or not
         */
        bool getsSeat;
};
#endif