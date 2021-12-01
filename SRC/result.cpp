#include "result.h"

namespace P {

	Result::Result() {
	}

	Result::~Result() {

	}

	void Result::addToTail(int numElectors, int partyNum, VoteSystem* _v) {
		resList* item = nullptr;
		try {
		 item = new resList{ partyNum ,numElectors,_v };
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		resHelperList.push_Back(*item);
	}



	void Result::operator=( Result& other) {

		//this->resHelperList = other.resHelperList;
		resHelperList.clear();
		auto itr = other.resHelperList.begin();
		auto end = other.resHelperList.end();
		resList* curr = nullptr;
		for (; itr != end; itr++) {
			try {
				curr = new resList{ itr->PartySerialNum,itr->numOfElectors,itr->v };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			resHelperList.push_Back(*curr);
		}


	}

	void Result::getData(int* numElectors, int* partySerialNumber, VoteSystem** vs, int index){
		auto itr = resHelperList.begin();
		for (int i = 0; i < index; i++) 
			itr++;

			*numElectors = itr->numOfElectors;
			*partySerialNumber = itr->PartySerialNum;
			try {
				*vs = new VoteSystem(*(itr->v));
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
	}
}


