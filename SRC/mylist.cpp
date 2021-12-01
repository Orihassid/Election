#include "mylist.h"
namespace P {

	MyList::MyList(): sizeOfList(0)
	{
	}



	void MyList::load(ifstream& in, Voter_Register* v){
		NodePerDistrict* curr ;
		RepresentList* repList;
		in.read(rcastc(&sizeOfList), sizeof(int));
		for (int i = 0; i < sizeOfList; i++) {
			try {
				repList = new RepresentList(in, v);
				curr = new NodePerDistrict{ *repList };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			districtRepList.push_Back(*curr);
		}
	}

	


	MyList::MyList(MyList& other) {
		*this = other;
	}

	MyList::~MyList(){
	}
	void MyList::addNode(int num) {

		while (num >= 1) {
			NodePerDistrict* item = nullptr;
			try {
				item = new NodePerDistrict;
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			num--;
			districtRepList.push_Back(*item);
		}
	}

	void MyList::operator=(MyList& other) {
		districtRepList.clear();
		auto itr = other.districtRepList.begin();
		auto end = other.districtRepList.end();
		for (; itr != end; itr++) {
			districtRepList.push_Back(*itr);
		}
	}

	void MyList::addNodeToTail(const NodePerDistrict* node) {

		NodePerDistrict* item = nullptr;
		try {
			new NodePerDistrict{ node->repList };
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		districtRepList.push_Back(*item);
	}

	void MyList::addRepresentor(Citizen* citizen, int districtNum) {
		auto itr = districtRepList.begin();
		while (districtNum > 1) {
			districtNum--;
			itr++;
		}
		itr->repList.addRepresentorToTail(citizen);

	}

	void MyList::displayRepresents(int numElectors, int districtNum) {
		auto itr = districtRepList.begin();
		
		while (districtNum > 1) {
			districtNum--;
			itr++;
		}
		itr->repList.dispaly(numElectors);

	}

	void MyList::save(ofstream& out) {
		auto itr = districtRepList.begin();
		updateSize();
		out.write(rcastcc(&sizeOfList), sizeof(int));
		for (int i = 0; i < sizeOfList; i++) {
			itr->repList.save(out);
			itr++;
		}
	}

	void MyList::updateSize()
	{
		sizeOfList = districtRepList.size();	
	}

	ostream& operator<<(ostream& os,  MyList& l) {
		auto itr = l.districtRepList.begin();
		auto end = l.districtRepList.end();
		int counter = 1;
		for (; itr != end; itr++)
			os << "ditrict number " << counter++ << " : " << itr->repList << endl;
		return os;
	}
}
