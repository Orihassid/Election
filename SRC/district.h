#pragma once
#include <iostream>
#include"citizen.h"
#include"List.h"

using namespace std;

namespace P {
	class Citizen;
	class Voter_Register;
	class District
	{
		// abstract class

	protected:
		//רשימת אזרחים בעלי זכות הצבעה
		//רשימת מי נבחר
		int counterPeople;//NodeCitizenList הגודל של הרשימה המקושרת 
		struct NodeCitizenList { Citizen* citizen; };
		myLST<NodeCitizenList> citizenList;
		int voteSum;//כמות כל ההצבעות 
		float precentOfVoters;//אחוז ההצבעות מכלל האזרחים
		int numOfelctors;
		int serialNumber;
		string name;
	public:



		static int counter;//מספר סידורי
		District(const string name, int size)throw(string);
		District(const District& other);
		District(ifstream& infile, Voter_Register* v, int* sizeArr, int*** arr);


		virtual ~District();

		const string getName()const { return name; }
		int getNumOfelctors()const { return numOfelctors; }
		int getCounterPeople()const { return counterPeople; }
		int getvoteNum()const { return voteSum; }
		void operator=(const District&);
		void addCitizen(const Citizen& c);
		friend ostream& operator<<(ostream&, const District&);
		virtual void toOs(ostream& os)const =0;
		virtual void addCitizenToTail(Citizen* c) = 0;
		int getSerialNumber()const { return serialNumber; }
		bool setCounterPeople(const int people);
		bool setVoteNum(const int voteNum);
		bool setPrecentOfVoters(float _precentOfVoters);
		int getPrecentOfVoters()const { return precentOfVoters; }
		virtual void save(ofstream& out);
		void saveCitizensId(ofstream& out);

	};

}