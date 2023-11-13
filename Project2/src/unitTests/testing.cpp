#include "gtest/gtest.h"

#include "../election.cpp"
#include "../candidate.cpp"
#include "../audit.cpp"
#include "../CPLCandidate.cpp"
#include "../CPLElection.cpp"
#include "../IRVBallot.cpp"
#include "../IRVCandidate.cpp"
#include "../IRVElection.cpp"
#include "../party.cpp"
#include "../POElection.cpp"
#include "../POBallot.cpp"
#include <ctime>
#include <chrono>
class AllTest : public ::testing::Test {
 public:
  void SetUp() { 
    // code here will execute just before the test ensues 
    // Election IRelection(filename);

  }
  void TearDown() {
    // code here will execute just after the test ends
  }
 protected:
};


// TEST_F(IRTest, Winner) {
//     EXPECT_EQ("Bernie", IRelection.getResults())
// }


//  
// Candidate Testing

// tests getName() & setname()
TEST_F(AllTest,candidateNameTest) {
  Candidate* foo = new Candidate("Ben");
  EXPECT_EQ("Ben",foo->getName()) << "Wrong Name";
  foo->setName("Tom");
  EXPECT_EQ("Tom",foo->getName()) << "Wrong Name";

}

// tests increaseVotes() & getVotes()
TEST_F(AllTest,candidateVotes) {
  Candidate* foo = new Candidate();
  foo->increaseVote();
  foo->increaseVote();
  
  EXPECT_EQ(2,foo->getVotes()) << "Votes should be 2";
}

// tests setParty() & getParty()
TEST_F(AllTest,candidateParty) {
  Candidate* foo = new Candidate();

  foo->setParty("Party");
  
  EXPECT_EQ("Party",foo->getParty()) << "Wrong Party";
}

//IRV Candidate Testing 

//tests constructor
TEST_F(AllTest,IRVcandidateNameTest) {
  IRVCandidate* foo = new IRVCandidate("Ben");
  EXPECT_EQ("Ben",foo->getName())  << "Wrong Name";;
}

//tests setInelection() and checklost()
TEST_F(AllTest,IRVcandidateInElection) {
  IRVCandidate* foo = new IRVCandidate("Ben") ;
  
  foo->setInElection(false);
  EXPECT_EQ(false,foo->getInElection())  << "Should be false";
  foo->setInElection(true);
  EXPECT_EQ(true,foo->getInElection()) << "Should be true";
}


// IRVBallot Testing 

// tests isempty() & Push()
TEST_F(AllTest,IRVBallotEmpty) {
  
  
  IRVBallot* irvballot = new IRVBallot();
  IRVCandidate* p = new IRVCandidate();

  EXPECT_EQ(irvballot->isempty(),true) << "Should be empty"; 
  irvballot->pushCandidates(p);
  EXPECT_EQ(irvballot->isempty(),false) << "Should have something in it"; 
}

//tests push(), getCount() and maybe pop()
TEST_F(AllTest,IRVBallotCount) {
  
  
  IRVBallot* irvballot = new IRVBallot();
  IRVCandidate* p = new IRVCandidate("x");
  IRVCandidate* p1 = new IRVCandidate("d");
  IRVCandidate* p2 = new IRVCandidate("p");
  
  irvballot->pushCandidates(p);
  irvballot->pushCandidates(p1);
  irvballot->pushCandidates(p2);

  EXPECT_EQ(3,irvballot->getCount()) << "Should be 3";

}

//tests setnumBallots() and getNumBallots()
TEST_F(AllTest,IRVBallotNumBallots) {
  
  
  IRVBallot* irvballot = new IRVBallot();
  irvballot->setnumBallots(3);
  

  EXPECT_EQ(3,irvballot->getnumBallots()) << "Should be 3";


}


//                                        IRV Election

// tests calcResults()
TEST_F(AllTest,IRVElectionResults) {
  
  
  IRVElection* irvElection = new IRVElection();
  

  EXPECT_EQ("Kleinberg (R)",irvElection->calcResults("../../testing/IRVTest6.csv")->getName()) << "Wrong winner";



}

// tests setNumCandidates(), getNumCandidates()
TEST_F(AllTest,IRVElectionnumCandidates) {
  
  
  IRVElection* irvElection = new IRVElection();
  
  irvElection->setnumCandidates(5);
  EXPECT_EQ(5,irvElection->getnumCandidates()) << "Wrong amount of candidates";



}

//                                        CPL Candidates

// tests setPartyRank(), getPartyRank()
TEST_F(AllTest,CPLParty) {
  
  
  CPLCandidate* cplcandidate = new CPLCandidate();
  cplcandidate->setPartyRank(3);
  

  EXPECT_EQ(3,cplcandidate->getPartyRank()) << "Should be 3";



}


//                                        CPL Election

//tests setnumcandidates() and getnumCandidates()
TEST_F(AllTest,CPLELectionCand) { 
  
  
  CPLElection* cplElection = new CPLElection();
  
  cplElection->setnumCandidates(6);
  EXPECT_EQ(6,cplElection->getnumCandidates()) << "wrong number of candidates";




}

TEST_F(AllTest,CPLELectionResults) { 
  
  
  CPLElection* cplElection = new CPLElection();
  
  EXPECT_EQ("Democratic", cplElection->calcResults("../../testing/CPLTest1.csv")->getPartyName()) << "wrong number of candidates";




}
                                           


// tests calcResults() // 
// TEST_F(Tests,CPLcalcResults) { //this one returns void
  
  
//   CPLElection* cplElection = new CPLElection();
  
  

//   EXPECT_EQ(3,cplElection->calcResults("CPLTest1.csv")) << "Should be 3"; // need to change this idk what output should be is



// }

//                                            Election

//tests breakTie();
TEST_F(AllTest,ElectionTieBreaker) {
  
  
  Election* election = new Election();
  
  bool bias = false;
  int winner1 = 0;
  int winner2 = 0;
  int timesRan = 1000;
  Candidate* x;
  Candidate* y;
  double maxMargin = (timesRan/2) * 1.10;
  double minMargin = (timesRan/2) * 0.90;

  for(int i = 0;i<timesRan;i++) {
    if(election->breakTie(x,y) == x) {
      winner1++;
    }
    else {
      winner2++;
    }
  }
    if (((winner1 > maxMargin) && (winner2 < minMargin)) || ((winner1 < minMargin) && (winner2 > maxMargin))) {
      bias = true;
    }

  EXPECT_EQ(false,bias) << "tie breaker is biased";



}

// tests setnumSeats(), getnumSeats()
TEST_F(AllTest,ElectionSeats) {
  
  
  Election* election = new Election();
  
  election->setnumSeats(5);
  EXPECT_EQ(5,election->getnumSeats()) << "wrong amount of seats";


}

// tests setNumBallots(),getnumBallots()
TEST_F(AllTest,ElectionBallots) {
  
  
  Election* election = new Election();
  
  election->setNumBallots(5);
  EXPECT_EQ(5,election->getnumBallots()) << "wrong amount of ballots";


}

// tests setNumCandidates(),getnumCand()
TEST_F(AllTest,ElectionCand) {
  
  
  Election* election = new Election();
  
  election->setNumCandidates(5);
  EXPECT_EQ(5,election->getnumCand()) << "wrong amount of candidates";



}

//tests construcotr and getElectionType()
TEST_F(AllTest,ElectionType) {
  
  
  Election* election = new Election("../../testing/CPLTest1.csv");
  
  election->setNumCandidates(5);
  EXPECT_EQ("CPL",election->getElectionType()) << "wrong election type";

  

}

//                                              Party

//tests setPartyName(),getPartyName()
TEST_F(AllTest,PartyName) {
  
  
  Party* party = new Party();
  
  party->setPartyName("R");
  EXPECT_EQ("R",party->getPartyName()) << "wrong Party";



}
// tests getPartyVotes(),incrementVotes()
TEST_F(AllTest,PartyIncVotes) {
  
  
  Party* party = new Party();
  EXPECT_EQ(0,party->getPartyVotes()) << "wrong amount of votes";

  party->incrementVotes();
  EXPECT_EQ(1,party->getPartyVotes()) << "wrong amount of votes";



}
// tests setPartySeats(),getPartySeats()
TEST_F(AllTest,PartySeats) {
  
  
  Party* party = new Party();
  
  party->setPartySeats(7);
  EXPECT_EQ(7,party->getPartySeats()) << "wrong number of seats";



}
//tests setRemainingVotes(),getRemainingVotes()
TEST_F(AllTest,PartyRemainingVotes) {
  
  
  Party* party = new Party();
  
  party->setRemainingVotes(12);
  EXPECT_EQ(12,party->getRemainingVotes()) << "wrong number of remaining votes";

  // EXPECT_EQ(p2,irvballot->pop()) << "Should be p2";
  // EXPECT_EQ(p1,irvballot->pop()) << "Should be p1";
  // EXPECT_EQ(p,irvballot->pop()) << "Should be p";

}
// tests setPartyVotes(5),getPartyVotes()
TEST_F(AllTest,PartySetVotes) {
  
  
  Party* party = new Party();
  
  party->setPartyVotes(5);
  EXPECT_EQ(5,party->getPartyVotes()) << "wrong number of partyvotes";

  

}

//                                                          AUDIT

// tests setfileOutput(), getfileOutput()
TEST_F(AllTest,AuditOutput) {
  
  
  Audit* audit = new Audit();
  
  audit->setfileOutput("IRVElection.txt");
  EXPECT_EQ("IRVElection.txt",audit->getfileOutput());
  

}

TEST_F(AllTest,AuditElectionType) {
  
  
  Audit* audit = new Audit();
  
  audit->setElectionType("IRV",1);
  EXPECT_EQ("IRV",audit->getelectionType());
  auto now = chrono::system_clock::now();
  time_t current_time = chrono::system_clock::to_time_t(now);
  tm local_time = *localtime(&current_time);

  EXPECT_EQ("IRV_" + to_string(local_time.tm_year + 1900) + "-" + to_string(local_time.tm_mon + 1) + "-" + to_string(local_time.tm_mday) + "_1.txt",audit->getfileOutput());
  

}


TEST_F(AllTest,AuditInvalidatedFile) {
  
  
  Audit* audit = new Audit();
  
  audit->setInvalidFile(1);
  auto now = chrono::system_clock::now();
  time_t current_time = chrono::system_clock::to_time_t(now);
  tm local_time = *localtime(&current_time);

  EXPECT_EQ("invalidated_" + to_string(local_time.tm_year + 1900) + "-" + to_string(local_time.tm_mon + 1) + "-" + to_string(local_time.tm_mday) + "_1.txt",audit->getfileOutput());
  

}

//                                          POBallots
//tests pushCandidates
TEST_F(AllTest,POBallotPush) {
  
  
  POBallot* ballot = new POBallot();

  Candidate* p = new Candidate("d");
  ballot->pushCandidates(p);
  EXPECT_EQ(1,ballot->candidates.size());

}

//tests getNumBallots and setNumBallots 
TEST_F(AllTest,POBallotNumBallots) {
  
  
  POBallot* ballot = new POBallot();

  ballot->setNumBallots(5);
  EXPECT_EQ(5,ballot->getNumBallots());

}
//                                  POElection

//tests getNumCandidates and setNumCandidates
TEST_F(AllTest,POElectionNumBallots) {
  
  
  POElection* election = new POElection();

  election->setNumCandidates(5);
  EXPECT_EQ(5,election->getNumCandidates());

}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv); 
  return RUN_ALL_TESTS();
}
