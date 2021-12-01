#pragma once
#include"Strings.h"
#include <fstream>
#include"district.h"
#include<string>
#include"List.h"
using namespace std;
namespace P {

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
	class District;

	class Citizen {

	private:
		string name;
		int id, yearBirth;
		District* district;
		int districtNum;
		int numOfChosenParty;//אחרי הבחירות
	public:
		Citizen();
		Citizen(const string name, int id, int yearBirth, District* district = nullptr)throw(string);
		Citizen(const Citizen& other);
		Citizen(ifstream& in);
		~Citizen();

		string getName()const { return name; }
		int getId()const { return id; }
		int getYearBirth()const { return yearBirth; }

		bool setName(const string name_);
		bool setId(const int id__);
		bool setYearBirth(const int yearBirth__);
		void operator=(const Citizen&);
		friend ostream& operator<<(ostream&, const Citizen&);
		bool setChosenNum(int partyNum);
		District* getDistrict() const { return district; };
		int getChosenParty()const { return numOfChosenParty; }
		void save(ofstream& out);
		int getDistrictNum() const { return districtNum; }
		void setDistrictPointer(District* d);
	};

}