#include "election_Simple.h"
namespace P {

	
	Election_Simple::Election_Simple(int d, int m, int y) :Election(d, m, y) {

	}

	Election_Simple::Election_Simple(ifstream& infile, Voter_Register* v, bool flagElection) : Election(infile, v, flagElection) {

	}

	Election_Simple::~Election_Simple()
	{
	}

	void Election_Simple::display() {
		voteList.displaySimpleElection();
	}

	void Election_Simple::toOs(ostream& os) const {
		os << "Simple Election " << endl;
	}


	

	void Election_Simple::operator=(const Election_Simple& other) {

	}


}