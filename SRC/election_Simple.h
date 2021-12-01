#pragma once
#include"election.h"

#include <fstream>
namespace P {
	class Election_Simple :public Election {
	private:



	public:
		Election_Simple(int d, int m, int y);
		Election_Simple(ifstream& infile, Voter_Register* v, bool flagElection);
		virtual ~Election_Simple();
		virtual void display()override;
		virtual void toOs(ostream& os)const;
		void operator=(const Election_Simple& other);


	};

}