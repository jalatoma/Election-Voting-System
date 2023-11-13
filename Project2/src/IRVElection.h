#ifndef _IRVELECTION_H
#define _IRVELECTION_H

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <list>
#include <iomanip>
#include "IRVCandidate.h"
#include "IRVBallot.h"
#include "audit.h"
#include "election.h"
using namespace std;


/**
 * @brief This is the IRV Election process that is inherited from the elction class
 */
class IRVElection : public Election {
    private:
    int numCandidates;
    vector<IRVBallot> ballots; 
    Audit auditFile;
    Audit invalidFile;
    vector<vector<int>> votesPerRound;
    vector<vector<int>> changeInVotes;
    vector<int> exhaustedPile; 
    vector <int> exhaustedPileChange;

    public:
    /**
     * @brief This is the default constructor
     */
    IRVElection();

    /**
     * @brief This eliminates a candidate from the election and distributes their votes
     * @param IRVBallot This is the ballots for the election
     * @param int The number of ballots 
     * @param int The number of candidates
     * @param ofstream The audit file being written to
     */
    void eliminateCandidate(IRVBallot* ballots, int numBallots, int numCandidates, ofstream &file); // getting rid of candidate with least votes

    /**
     * @brief This gets the number of candidates running in the election
     * @return An int of how mnay candidates there are
     */
    int getnumCandidates();

    /**
     * @brief Sets the nuber of candidates
     * @param int This is how many candidates we want to set it to
     */
    void setnumCandidates(int number);

    /**
     * @brief Calculates results pf the election
     * @param string This is the file we're reading from
     * @return The candidate that won
     */
    Candidate* calcResults(string filename);

    /**
     * @brief Prints the table for the election
     * @param IRVBallot This is the ballots that we need to parse through
     * @param int This is the number of candidates in the election
     * @param int This is the number of ballots
     */
    void printTable(IRVBallot* ballots, int numCandidates, int numBallots);


    static int count;
    // string output;
    int rounds;

};

#endif