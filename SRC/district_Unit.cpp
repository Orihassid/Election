#include "district_Unit.h"
namespace P {
	District_Unit::District_Unit(const string districtName, int size) :District(districtName, size) {

	}

	District_Unit::District_Unit(ifstream& in, Voter_Register* v, int* sizeArr, int** arr) : District(in, v, sizeArr, &arr)
	{
	}

	void District_Unit::addCitizenToTail(Citizen* c) {
		NodeCitizenList* item = nullptr;
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

	void District_Unit::toOs(ostream& os) const {
		os << "type - Unit district" << endl;
	}

}