#pragma once
#include "citizen.h"
#include "mylist.h"
#include <fstream>

namespace P {
	class Party {
	private:
		int serialNumber;
		string name;
		Citizen* candidate;
		MyList list;
	public:
		static int counter;
		Party(const string name, int id, Citizen* c, int numofDistricts);
		Party(Party& other);
		Party(ifstream& in, Voter_Register* v);
		~Party();

		string getName() const { return name; }
		int getSerialNumber() const { return serialNumber; }
		Citizen* getCandidate() const { return candidate; }
		void operator=(Party& other);
		friend ostream& operator<<(ostream&,Party&);
		MyList& getList() { return list; }
		void save(ofstream& out);
	};

}