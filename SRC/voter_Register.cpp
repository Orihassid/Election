#include "voter_Register.h"

namespace P {

	Voter_Register::Voter_Register() :sizeList(0) {
	}

	Voter_Register::Voter_Register(ifstream& in) : Voter_Register() {
		in.read(rcastc(&sizeList), sizeof(int));
		bool flag;
		Citizen* c;
		Node* curr;
		auto itr = voterList.begin();
		for (int i = 0; i < sizeList; i++) {
			try {
				c = new Citizen(in);
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			in.read(rcastc(&flag), sizeof(bool));
			try {
				curr = new Node{ c,flag };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			addNodeToTail2(curr);
		}
	}

	Voter_Register::Voter_Register( Voter_Register& other)
	{
		*this = other;
	}

	void Voter_Register::operator=(Voter_Register& other) {
		Node* curr = nullptr;
		this->sizeList = other.sizeList;
		voterList.clear();
		auto itr = other.voterList.begin();
		auto end = other.voterList.end();
		// this->voterList = other.voterList;
		for (; itr != end; itr++) {
			try {
				curr = new Node{ itr->c,itr->vote };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			voterList.push_Back(*curr);
		}
	}

	Voter_Register::~Voter_Register()
	{

	}

	void Voter_Register::addNodeToTail(Citizen& c) {
		Citizen* citizen = nullptr;
		Node node;
		try {
			citizen = new Citizen{ c };
			node = { citizen,false };
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		voterList.push_Back(node);
	}

	void Voter_Register::updateSize() {
		sizeList = voterList.size();
	}

	void Voter_Register::save(ofstream& out) {

		auto itr = voterList.begin();
		updateSize();
		out.write(rcastcc(&sizeList), sizeof(int));

		for (int i = 0; i < sizeList; i++) {

			itr->c->save(out);
			out.write(rcastcc(&itr->vote), sizeof(bool));
			itr++;
		}

	}

	Citizen* Voter_Register::vote(int partyNum, int id)throw(string,bool) {
		myLST<Node>::iterator itr = voterList.begin();
		myLST<Node>::iterator end = voterList.end();
		bool flag = false;
		for (; itr != end; itr++)
		{
			if (itr->c->getId() == id) {
				if (itr->vote == true) {
					string msg = "double Vote";
					throw msg;
				}
				flag = true;
				itr->vote = true;
				itr->c->setChosenNum(partyNum);
				return itr->c;
			}
		}
		if (!flag) {
			throw(flag);
		}
		return nullptr;
	}

	ostream& operator<<(ostream& os, Voter_Register& v) {
		auto itr = v.voterList.begin();
		auto end = v.voterList.end();

		for (; itr != end; itr++) {
			os << *(itr->c) << endl;
		}
		return os;
	}


	Citizen* Voter_Register::candidateParty(int id) {
		myLST<Node>::iterator itr = voterList.begin();
		myLST<Node>::iterator end = voterList.end();

		for (; itr != end; itr++)
		{
			if ((itr->c->getId()) == id) {
				return itr->c;
			}

		}
		return nullptr;
	}

	void Voter_Register::displayCitizens() {
		myLST<Node>::iterator itr = voterList.begin();
		

		for (int i=0;i<voterList.size();i++){
			cout << *(itr->c);
			itr++;

		}
	}

	bool Voter_Register::updateCitizen(int id, Citizen** citizen)
	{
		myLST<Node>::iterator itr = voterList.begin();
		myLST<Node>::iterator end = voterList.end();

		for (; itr != end; itr++)

		{
			if (itr->c->getId() == id) {
				*citizen = itr->c;
				return true;
			}
		}
		return false;
	}

	Citizen* Voter_Register::getCitizen()
	{
		auto itr = voterList.begin();
		auto end = voterList.end();
		auto temp = voterList.begin();
		for (; itr != end; itr++)
		{
			temp = itr;
			temp++;
			if (!(temp != end))
				return itr->c;
		}
		return nullptr;
	}

	void Voter_Register::addNodeToTail2(Node* node) {
		voterList.push_Back(*node);
	}
	void Voter_Register::getData(int * DistrictId,int index)
	{
		auto itr = voterList.begin();
		for (int i = 0; i < index; i++)
			itr++;
		*DistrictId = itr->c->getDistrictNum();
	}
	void Voter_Register::setData(District* d,int index)
	{
		auto itr = voterList.begin();
		for (int i = 0; i < index; i++)
			itr++;
		itr->c->setDistrictPointer(d);

	}
}