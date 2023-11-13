#include "audit.h"

Audit::Audit() {
    electionType = " ";
    fileOutput = " ";
}

void Audit::setElectionType(string election, int count){

    // getting the time on the system for the name of audit file
    auto now = chrono::system_clock::now();
    time_t current_time = chrono::system_clock::to_time_t(now);

    tm local_time = *localtime(&current_time);

    electionType = election;
    // create the file name for the audit file
    fileOutput = electionType + "_" + to_string(local_time.tm_year + 1900) + "-" + to_string(local_time.tm_mon + 1) + "-" + to_string(local_time.tm_mday) + "_" + to_string(count) + ".txt"; //name here
}

void Audit::setInvalidFile(int count){

    // getting the time on the system for the name of audit file
    auto now = chrono::system_clock::now();
    time_t current_time = chrono::system_clock::to_time_t(now);

    tm local_time = *localtime(&current_time);

    // create the file name for the audit file
    fileOutput = "invalidated_" + to_string(local_time.tm_year + 1900) + "-" + to_string(local_time.tm_mon + 1) + "-" + to_string(local_time.tm_mday) + "_" + to_string(count) + ".txt"; //name here
}

ofstream Audit::OpenFile(string filename){
    // opens the audit file
    ofstream file;
    file.open(filename);
    return file;
}

string Audit::getfileOutput() {
    return fileOutput;
}

string Audit::getelectionType() {
    return electionType;
}

void Audit::setfileOutput(string name) {
    fileOutput = name;
}
