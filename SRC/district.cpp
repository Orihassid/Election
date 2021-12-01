#include "district.h"
#include "Strings.h"

namespace P {

	int District::counter = 0;



	District::District(const string name, int size) throw(string){
		string msg = "num electors must be positive";
		if (size >= 0)
			this->numOfelctors = size;
		else
			throw msg;
		this->serialNumber = ++counter;
		this->name = name;
		this->counterPeople = 0;
		this->voteSum = 0;
		this->precentOfVoters = 0;

		

	}

	District::District(const District& other) {

		*this = other;
	}

	District::District(ifstream& infile, Voter_Register* v, int* sizeArr, int*** arr){
		Citizen* c;
		int citizenId, nameLen,sizeOfpeople;
		counterPeople = 0;
		infile.read(rcastc(&sizeOfpeople), sizeof(int));
		*sizeArr = sizeOfpeople;
		int* res;
		try {
		res = new int[sizeOfpeople];
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		char* temp;
		for (int i = 0; i < sizeOfpeople; i++)
		{
			infile.read(rcastc(&citizenId), sizeof(int));
			res[i] = citizenId;
		}
		**arr = res;
		infile.read(rcastc(&voteSum), sizeof(int));
		infile.read(rcastc(&precentOfVoters), sizeof(float));
		infile.read(rcastc(&serialNumber), sizeof(int));
		infile.read(rcastc(&numOfelctors), sizeof(int));
		infile.read(rcastc(&nameLen), sizeof(int));
		try {
			temp = new char[nameLen + 1];
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		infile.read(rcastc(temp), nameLen);
		temp[nameLen] = '\0';
		this->name = temp;
		delete[]temp;
	}


	District::~District() {

	}



	void District::operator=(const District& other) {
		
		*this = other;

	}

	void District::addCitizen(const Citizen& c) {
		Citizen* citizen = nullptr;
		try {
		 citizen = new Citizen(c);
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		NodeCitizenList node{ citizen };
		citizenList.push_Back(node);

		
	}


	bool District::setCounterPeople(const int people) {
		if (people >= 0) {
			this->counterPeople++;
			return true;
		}
		else {
			return false;
		}
	}

	bool District::setVoteNum(const int voteNum) {
		if (voteNum >= 0) {
			this->voteSum = voteNum;
			return true;
		}
		else {
			return false;
		}
	}

	bool District::setPrecentOfVoters(float _precentOfVoters) {

		if (_precentOfVoters >= 0 && _precentOfVoters <= 100) {
			this->precentOfVoters = _precentOfVoters;
			return true;
		}
		return false;
	}

	void District::save(ofstream& out) {
		saveCitizensId(out);

		out.write(rcastcc(&voteSum), sizeof(int));
		out.write(rcastcc(&precentOfVoters), sizeof(float));
		out.write(rcastcc(&serialNumber), sizeof(int));
		out.write(rcastcc(&numOfelctors), sizeof(int));
		int sizeOfname = name.size();
		out.write(rcastcc(&sizeOfname), sizeof(int));
		out.write(rcastcc(name.c_str()), sizeOfname);





	}

	void District::saveCitizensId(ofstream& out) {
		auto itr = citizenList.begin();
		int id;
		out.write(rcastcc(&counterPeople), sizeof(int));
		for (int i = 0; i < counterPeople; i++) {
			id = itr->citizen->getId();
			out.write(rcastcc(&id), sizeof(int));
			itr++;
		}
	}





	ostream& operator<<(ostream& os, const District& d)
	{
		os << d.serialNumber << ". name : " << d.name << endl;
		d.toOs(os);
		os << "number of representors " << d.numOfelctors << endl;
		return os;
	}


}