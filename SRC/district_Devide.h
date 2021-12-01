#pragma once
#include "district.h"

namespace P {
	class District_Devide :public District {
	
	
	public:
		District_Devide(const string, int);
		District_Devide();
		District_Devide(ifstream& in, Voter_Register* v, int* sizeArr, int** arr);
		virtual~District_Devide();
		virtual void addCitizenToTail(Citizen* c) override;
		virtual void toOs(ostream& os)const override;
	};
}

