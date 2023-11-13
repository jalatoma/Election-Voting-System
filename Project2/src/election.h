#ifndef _ELECTION_H
#define _ELECTION_H

#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "candidate.h"

using namespace std;

/**
 * @brief Main election class that runs CPL and IRV
 */
class Election{
    private:
    int numCand;
    int numBallots;
    int numSeats;
    string electionType;
    vector<Candidate> candidates;
    vector<Candidate> winners;

    string file;
    ofstream finalFile;

    stringstream ballots;
    
    public:
    /**
     * @brief Default constructor
     */
    Election();

    /**
     * @brief Constructor that sets the input filename for the election
     * @param string The input file that we are reading from
     */
    Election(const string& filename);

    /**
     * @brief Gets additional info from the user if needed
     */
    void getAdditionalInfo();

    /**
     * @brief Gets the election that we are running (CPL or IRV)
     * @return String of the election type
     */
    string getElectionType();

    /**
     * @brief Sets the number of candidates in the election
     * @param int The number of candidates we want to set it to
     */
    void setNumCandidates(int cands);

    /**
     * @brief Sets the number of ballots in the election
     * @param int The number of ballots we want to set it to
     */
    void setNumBallots(int ballots);

    /**
     * @brief Gets the number of candidates
     * @return The int value of how many candidates
     */
    int getnumCand();

    /**
     * @brief Gets the number of ballots in the election
     * @return Int value of how many ballots
     */
    int getnumBallots();

    /**
     * @brief Gets number of seats available
     * @return The int value of how mnay seats
     */
    int getnumSeats();

    /**
     * @brief Sets the number of seats in the election
     * @param int The number of seas we want to set it to
     */
    void setnumSeats(int seats);

    void increaseBallots(int x);

    /**
     * @brief Breaks ties between 2 people in election
     * @param Candidate The first candidate in the tie
     * @param Candidate The second candidate in the tie
     * @return The candidate that won
     */
    Candidate* breakTie(Candidate* cand1, Candidate* cand2);
  /**
     * @brief Breaks ties between 2 parties in election
     * @param Candidate The first party in the tie
     * @param Candidate The second party in the tie
     * @return The party that won
     */
    int breakTie(int party1, int party2);

    void combine(string filename,int count);

    /**
     * @brief This stores the winner, of type Candidate
     */
    Candidate* winner;
    int headers;

};

#endif