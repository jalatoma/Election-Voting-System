#ifndef _CANDIDATE_H
#define _CANDIDATE_H

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief This is the main candidate class, holds candidates of an election
 */
class Candidate{
    private:
        string name;
        string party;

    public:
        /**
         * @brief Constructor for candidate class, initializes private variables
         */
        Candidate();

        /**
         * @brief Constructor for candidate class, initializes candidate name variables
         * @param string This is the candidate name we want to set it to
         */
        Candidate(string candidateName);

        /**
         * @brief Gets the votes
         * @return Returns vote count
         */
        int getVotes();

        /**
         * @brief Gets the name of the candidate
         * @returns A string of the candidate name
         */
        string getName();

        /**
         * @brief Gets the party name
         * @returns String of the party name
         */
        string getParty();

        /** 
         * @brief Sets the party name to a specified x
         * @param string This is the party we are setting it to
         */
        void setParty(string x);

        /**
         * @brief Increases the vote count by 1
         */
        void increaseVote();

        /**
         * @brief Holds the vote count
         */
        double votes;

        /**
         * @brief Sets the name variable to setName
         * @param string This is the name we are setting it to 
         */
        void setName(string setName);
};

#endif