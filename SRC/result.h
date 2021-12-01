#pragma once
#include <fstream>
#include"List.h"
#include"VoteSystem.h"

namespace P {
	class VoteSystem;
	class Result {
	private:

		struct resList {
			int  PartySerialNum = 0;
			int numOfElectors = 0;
			VoteSystem* v;
		};

		myLST<resList>resHelperList;
		int sizeList;
	public:
		Result();
		~Result();
		void addToTail(int numElectors, int partyNum, VoteSystem* _v);
		void operator=( Result&);
		myLST<resList> getList() {return resHelperList;}
	void getData(int*, int*, VoteSystem**, int );
		
	
	};

}

