#include "citizen.h"
#include "district.h"

namespace P {
	Citizen::Citizen() {
	}

	Citizen::Citizen(const string name, int id, int yearBirth, District* district)throw(string){
		if (yearBirth > 0)
			this->yearBirth = yearBirth;
		else
			throw "in valid year of birth. please try again";
		this->name = name;
		this->id = id;
		this->yearBirth = yearBirth;
		this->numOfChosenParty = 0;
		this->district = district;
	}

	Citizen::Citizen(const Citizen& other) {
		
		*this = other;	
	}

	Citizen::Citizen(ifstream& in) {
		int nameLen;
		char* temp;
		in.read(rcastc(&nameLen), sizeof(int));
		try {
			temp = new char[nameLen + 1];
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		in.read(rcastc(temp), nameLen);
		temp[nameLen] = '\0';
		this->name = temp;
		delete []temp;
		in.read(rcastc(&id), sizeof(int));
		in.read(rcastc(&yearBirth), sizeof(int));
		in.read(rcastc(&districtNum), sizeof(int));
		in.read(rcastc(&numOfChosenParty), sizeof(int));


	}

	Citizen::~Citizen() {

		
	}


	bool Citizen::setName(const string name_) {
		
		name = name_;
		return true;
	}

	bool Citizen::setId(const int id_) {
		id = id_;
		return true;
	}

	bool Citizen::setYearBirth(const int yearBirth_)
	{
		yearBirth = yearBirth_;
		return true;
	}


	void Citizen::operator=(const Citizen& other) {
		name =other.name;
		id = other.id;
		yearBirth = other.yearBirth;
		district = other.district;
	}

	bool Citizen::setChosenNum(int partyNum) {
		this->numOfChosenParty = partyNum;
		return true;
	}

	void Citizen::save(ofstream& out) {
		int sizeOfname = name.size();
		out.write(rcastcc(&sizeOfname), sizeof(int));
		out.write(rcastcc(name.c_str()), sizeOfname);
		out.write(rcastcc(&id), sizeof(int));
		out.write(rcastcc(&yearBirth), sizeof(int));
		this->districtNum = this->district->getSerialNumber();
		out.write(rcastcc(&districtNum), sizeof(int));
		out.write(rcastcc(&numOfChosenParty), sizeof(int));
	}

	void Citizen::setDistrictPointer(District* d)
	{
		district = d;
	}


	ostream& operator<<(ostream& os, const Citizen& c)
	{
		os << "Name - " << c.name << endl << "Id - " << c.id << endl << "Year - " << c.yearBirth << endl << "District name -" << c.district->getName() << endl;

		return os;
	}
}