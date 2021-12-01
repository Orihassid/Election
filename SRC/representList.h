#pragma once
#include <fstream>
#include "citizen.h"
#include"voter_Register.h"

namespace P {
	class RepresentList {
	private:
		struct NodeRepresentListPerDistrict {
			Citizen* citizen;
		};

		myLST< NodeRepresentListPerDistrict>citizenRepList;
		int sizeOfList;
	public:
		RepresentList();
		RepresentList(ifstream& in, Voter_Register* v);
		RepresentList(NodeRepresentListPerDistrict* h, NodeRepresentListPerDistrict* t);
		~RepresentList();
		void operator=(RepresentList& other);
		void addNodeToTail(NodeRepresentListPerDistrict* node);
		void addRepresentorToTail(Citizen* citizen);
		friend ostream& operator<<(ostream&,RepresentList&);
		void dispaly(int numElectors);
		void save(ofstream& out);
		void updateSize();
		 void addRepresentorToTailFromFile(NodeRepresentListPerDistrict*node);
	};

}