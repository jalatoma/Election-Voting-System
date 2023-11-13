# the compiler
CC = g++

# compiler flags (TBD)
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS = -Wall -g -lgtest -lpthread -lgmock 

#
DEPS = election.h candidate.h audit.h CPLCandidate.h CPLElection.h IRVBallot.h IRVCandidate.h IRVElection.h party.h POElection.h POBallot.h 
SRCS= main.cpp election.cpp candidate.cpp audit.cpp CPLCandidate.cpp CPLElection.cpp IRVBallot.cpp IRVCandidate.cpp IRVElection.cpp party.cpp POElection.cpp POBallot.cpp 
TARGET = test
OBJS=$(SRCS:.cpp=.o)

# build executable
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CLAGS) $(OBJS) -o $(TARGET)

# delete executable files
clean: 
	rm -f *.o 
	rm -f *.txt
	rm -f *.csv
