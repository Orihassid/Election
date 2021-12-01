#pragma once
#include "party.h"
#include"district_Devide.h"
#include"district_Unit.h"
#include"List.h"

namespace P {
	class District;
	class VoteSystem {
		

	private:
		
		struct NodeVote {
			Party* party;
			int counter;
			float votePrecents;
			int numOfRepresentor;
			
			//NodeVote* next;
		};
		myLST<NodeVote>NodeVoteList;
		float districtVotes;
		//NodeVote* head, * tail;
		int sizeList;
		int serialNumber;

	public:

		VoteSystem();
		VoteSystem(VoteSystem& other, bool fromFile);
		VoteSystem(VoteSystem& other);
		VoteSystem(ifstream& in);
		void LoadVote(ifstream& in);
		~VoteSystem();
		void operator=( VoteSystem&other);
		static int counter2;//מספר סידורי
		void addPartyNodeToTail(Party* p);
		void updatePartyVote(int partyNum);
		int countVotes();
		bool setDistrictVotes(const int districtVotes);
		void updatePrecents();
		void updateVoteSystemNodes(District& district);
		Party* getWinParty();
		void displayRegular(District& d);
		void displaySimple(District& d);
		static int CompareRepresentors(const void* a, const void* b);
		static int CompareVotes(const void* a, const void* b);
		void displayRepresentors(Party* p, int numElectors, int districtNum);
		float* updateRepresentorsPerParty(int numOfelctors, int voteNum, float* arr, float size);
		void printRepresentors(Party* p, int numRepresentors, int numDistrict);
		void updateNodeVote(float* arr, int size);
		void displayPartyDetails(NodeVote** arr, int size, District& d);
		void save(ofstream& out);
		void updateSize();
		void setNodeDetails(Party* p, int numVotesPerParty, float  precentVote, int  numElectors);
		void addNodeToTail(NodeVote* node);
		myLST<NodeVote> getList() { return NodeVoteList;}
		static bool wasLoad;
		void getData(int, int*);
		void getSizeFromList(int*);
	};
}
