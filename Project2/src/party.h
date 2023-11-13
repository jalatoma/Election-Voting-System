#ifndef _PARTY_H
#define _PARTY_H

#include <iostream>
#include <string>
#include <vector>
#include "CPLCandidate.h"

/**
 * @brief This is the party class used for CPL
 */
class Party {
    private:
        string partyName;
        int votes;
        int seats;
        int remainingVotes;
    public: 
        /**
         * @brief This is the default constructor
         */
        Party();

        /**
         * @brief This sets the party name
         * @param string This is the party name we want to set it to
         */
        Party(string name);
        // getters
        
        /**
         * @brief This gets the current party name
         * @return This returns the party name
         */
        string getPartyName();

        /**
         * @brief This gets the current party votes
         * @return This returns the party votes
         */
        int getPartyVotes();

        /**
         * @brief This gets the current party seats
         * @return This returns the party seats
         */
        int getPartySeats();

        /**
         * @brief This gets the remaining party votes
         * @return This returns the  remaining party votes
         */
        int getRemainingVotes();
        //setters

        /**
         * @brief This sets the current party name
         * @param string This is what we want to set it to
         */
        void setPartyName(string name);

         /**
         * @brief This sets the current party votes
         * @param int This is what we want to set it to
         */
        void setPartyVotes(int partyVotes);

         /**
         * @brief This sets the current party seats
         * @param int This is what we want to set it to
         */
        void setPartySeats(int partySeats);

         /**
         * @brief This sets the remaining party votes
         * @param int This is what we want to set it to
         */
        void setRemainingVotes(int votes);

        /**
         * @brief This increments the votes for the party by 1
         */
        void incrementVotes();

        /**
         * @brief This holds the candidates for the party
         */
        vector<CPLCandidate*> candidates;

};
#endif