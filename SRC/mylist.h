#pragma once
#include<fstream>
#include "representList.h"
#include "List.h"
namespace P {
	class MyList
	{
	private:
		struct NodePerDistrict {
			RepresentList repList;
		};
		myLST< NodePerDistrict>districtRepList;
		int sizeOfList;
	public:
		MyList();
		MyList(MyList& other);
		~MyList();
		void addNode(int num);
		void operator=( MyList& other);
		void addNodeToTail(const NodePerDistrict* node);
		void addRepresentor(Citizen* citizen, int districtNum = 1);
		friend ostream& operator<<(ostream&,MyList&);
		void displayRepresents(int numElectors, int districtNum);
		void save(ofstream& out);
		void updateSize();
		void load(ifstream& in, Voter_Register* v);
	};
}

