#pragma once
#include"citizen.h"
#include<list>
namespace P {

	class Voter_Register{
		

	private:                      
		struct Node {
			Citizen* c;
			bool vote = false;
			
		};
		myLST<Node>voterList;
		int sizeList;

	public:
		Voter_Register();
		Voter_Register(ifstream& in);
		Voter_Register( Voter_Register&other);
		void operator=( Voter_Register&);
		~Voter_Register();
		void addNodeToTail(Citizen& c);
		void updateSize();
		void save(ofstream& out);
		Citizen* vote(int partyNum, int id);
		Citizen* candidateParty(int id);
		void displayCitizens();
		bool updateCitizen(int id, Citizen** citizen);
		Citizen* getCitizen();
		void addNodeToTail2(Node* node);
		myLST<Node> getList() { return voterList; }
		friend ostream& operator<<(ostream&, Voter_Register&);
		int getSizeList() { return voterList.size();}
		void getData(int *,int);
		void setData(District*,int);
			
	};
}