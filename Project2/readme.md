# Election Voting System

### Group Members: Jacynda Alatoma, Naren Nandyal, Long Nguyen, Ananya Vegesna

### File Structure:
  * src
	* audit.h/.cpp
	* candidate.h/.cpp
	* CPLCandidate.h/.cpp
	* CPLElection.h/.cpp
	* election.h/.cpp
	* IRVballot.h/.cpp
	* IRVCandidate.h/.cpp
	* IRVElection.h/.cpp
	* party.h/.cpp
	* POBallot.h/.cpp
	* POElection.h/.cpp
	* main.cpp
	* Makefile
	* unit_test
		* testing.cpp
		* Makefile
  * documentation
	* Doxyfile
	* html
		* index.html (the site for Doxygen comments)
		* etc…
	* latex
		* etc…
  * testing
	* CSV Files for Testing
	* Testing Log
  * product_backlogs
  	* The initial product backlog can be found here
  * sprint_backlog
  	* The sprint backlogs for the previous 2 weeks can be found here

### How to run the elections in <code>src</code>
Run <code>make all</code> and then in terminal run <code>./test filename</code> where <code>filename</code> is the name of the CSV file with the ballots. This should be in the format of example: <code>../testing/POTest1.csv</code>, since our CSV testing files are in a different directory. For multiple files, all the files names for the election can be entered, with a space in between each CSV election file. For example it would look something like this in terminal: <code>./test ../testing/POTest1.csv ../testing/POTest2.csv</code>.

### How to run the Google tests in <code>unit_test</code>
Run <code>make test</code> and then in terminal run <code>./testing</code> and then the successes and failures will show up in the terminal for the tests.

