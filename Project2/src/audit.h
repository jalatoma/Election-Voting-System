#ifndef _AUDIT_H
#define _AUDIT_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <chrono>

using namespace std;

/**
 * @brief This is the audit class which creates and adds output to the audit file
 */
class Audit {
    private:
    string fileOutput;
    string electionType;

    public:
    /**
     * @brief This is a constructor for the audit class, sets fileOutput and electionType as blank
     */
    Audit();

    /**
     * @brief Sets the election type variable
     * @param string Is the election that we're setting it to
     */
    void setElectionType(string election, int count);

    /**
     * @brief Opening the audit file to write to
     * @param string This is the filename we are opening
     * @return The output audit file
     */

    void setInvalidFile(int count);

    ofstream OpenFile(string filename);

    /**
     * @brief Gets the file output name
     * @return Returns the file name
     */
    string getfileOutput();

    /**
     * @brief Gets the election type name
     * @return Returns election type
     */
    string getelectionType();

    /**
     * @brief Sets the file name
     * @param string Is the filename we want to set it to
     */
    void setfileOutput(string name);

     /**
     * @brief Gets the number of election
     * @return Returns the number
     */
    int getnumberOfElection();

    /**
     * @brief Sets the election number
     * @param int number to set it to
     */
    void setnumberOfElection(int num);

};

#endif