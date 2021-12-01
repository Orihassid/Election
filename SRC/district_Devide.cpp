#include "district_Devide.h"
namespace P {
	District_Devide::District_Devide(const string districtName, int size) :District(districtName, size) {
	}



	District_Devide::District_Devide(ifstream& in, Voter_Register* v, int* sizeArr, int** arr) : District(in, v, sizeArr, &arr)
	{
		

	}

	District_Devide::~District_Devide()
	{
	}
	void District_Devide::addCitizenToTail(Citizen* c) {
		NodeCitizenList* item;
		try {
		item = new NodeCitizenList{ c };
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		this->setCounterPeople(1);
		citizenList.push_Back(*item);
		
	}
	void District_Devide::toOs(ostream& os) const {
		os << "type - devide district" << endl;
	}
}