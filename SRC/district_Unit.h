#pragma once
#include "district.h"
namespace P {
	class District_Unit :public District {
	private:

	public:
		District_Unit(const string districtName, int size);
		District_Unit(ifstream& in, Voter_Register* v, int* sizeArr, int**arr);
		virtual void addCitizenToTail(Citizen* c) override;
		virtual void toOs(ostream& os)const override;
	};

}