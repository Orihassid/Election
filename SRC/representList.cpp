#include "representList.h"

namespace P {



	RepresentList::RepresentList() :sizeOfList(0)
	{
	}

	RepresentList::RepresentList(ifstream& in, Voter_Register* v){
		NodeRepresentListPerDistrict* curr;
		Citizen* c;
		int citizenId;
		in.read(rcastc(&sizeOfList), sizeof(int));
		for (int i = 0; i < sizeOfList; i++)
		{
			in.read(rcastc(&citizenId), sizeof(int));
			v->updateCitizen(citizenId, &c);
			try {
				curr = new NodeRepresentListPerDistrict{ c };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			citizenRepList.push_Back(*curr);
		
		}

	}

	RepresentList::RepresentList(NodeRepresentListPerDistrict* h, NodeRepresentListPerDistrict* t){

	}

	RepresentList::~RepresentList() {


	}

	void RepresentList::operator=(RepresentList& other) {
		citizenRepList.clear();
		auto itr = other.citizenRepList.begin();
		auto end = other.citizenRepList.end();
		NodeRepresentListPerDistrict* item;
		for (; itr != end; itr++) {
			try {
				item = new NodeRepresentListPerDistrict{ itr->citizen };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			addNodeToTail(item);
		}
	}
	void RepresentList::addNodeToTail(NodeRepresentListPerDistrict* node) {

		NodeRepresentListPerDistrict* item = nullptr;
		try {
		item = new NodeRepresentListPerDistrict;
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		item->citizen = node->citizen;
		delete node;
		citizenRepList.push_Back(*item);
	}

	void RepresentList::addRepresentorToTail(Citizen* citizen) {
		try {
			addNodeToTail(new NodeRepresentListPerDistrict{ citizen });
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
	}
	void RepresentList::dispaly(int numElectors) {
		
		auto itr = citizenRepList.begin();
		auto end = citizenRepList.end();
		int sizeRep = citizenRepList.size();
		int counter = 1;
		for (; (numElectors >= 1) && (itr != end); itr++){
			if (sizeRep--)
				cout << "represent " << counter++ << "-" << *(itr->citizen) << endl;

			numElectors--;
		}
	}
	void RepresentList::save(ofstream& out)
	{
		auto itr = citizenRepList.begin();
		auto end = citizenRepList.end();
		updateSize();
		int id;
		out.write(rcastcc(&sizeOfList), sizeof(int));
		for (int i = 0; i < sizeOfList; i++)
		{
			id = itr->citizen->getId();
			out.write(rcastcc(&id), sizeof(int));
			itr++;
		}


	}
	void RepresentList::updateSize()
	{
	this->sizeOfList= citizenRepList.size();
	}
	void RepresentList::addRepresentorToTailFromFile(NodeRepresentListPerDistrict* node)
	{
		citizenRepList.push_Back(*node);
	}
	ostream& operator<<(ostream& os,  RepresentList& r) {
		cout << endl;
		auto itr = r.citizenRepList.begin();
		auto end =r.citizenRepList.end();
		int size = r.citizenRepList.size();
		int counter = 1;
		 {
			for (; itr != end; itr++)
				if (size--)
					os << "represent number " << counter++ << " : " << itr->citizen->getName() << endl;
				else if (r.citizenRepList.size())
					break;
				else
					os << "there is no represents " << endl;

		}

		return os;
	}
}
