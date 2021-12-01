#include "party.h"
#include "Strings.h"
namespace P
{

	int Party::counter = 0;
	Party::Party(const string name, int id, Citizen* c, int numofDistricts) {
		this->serialNumber = ++counter;
		this->name = name;
		this->candidate = c;
		list.addNode(numofDistricts);
	}



	Party::Party(Party& other)
	{
		
		*this = other;
	}

	Party::Party(ifstream& in, Voter_Register* v){
		int nameLen,citizenId;
		Citizen* c;
		in.read(rcastc(&serialNumber), sizeof(int));
		in.read(rcastc(&nameLen), sizeof(int));
		char* temp = nullptr;
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
		delete[]temp;
		in.read(rcastc(&citizenId), sizeof(int));
		v->updateCitizen(citizenId, &c);
		candidate = c;
		list.load(in, v);


	}


	void Party::operator=( Party& other) {
		
		
		name = other.name;
		serialNumber = other.serialNumber;
		candidate = other.candidate;
		list = other.list;

	}

	void Party::save(ofstream& out) {

		out.write(rcastcc(&serialNumber), sizeof(serialNumber));
		int sizeOfname = name.size();
		out.write(rcastcc(&sizeOfname), sizeof(int));
		out.write(rcastcc(name.c_str()), sizeOfname);
		int id = candidate->getId();
		out.write(rcastcc(&id), sizeof(int));
		list.save(out);

	}

	Party::~Party() {
		
	}

	ostream& operator<<(ostream& os,  Party& p) {
		os << p.serialNumber << ". name : " << p.name << endl << "candidate party: " << p.candidate->getName() << endl << p.list;
		return os;
	}





}