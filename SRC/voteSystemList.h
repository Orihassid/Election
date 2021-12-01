#pragma once
#include"VoteSystem.h"
#include"result.h"


namespace P {
	class District;

	class VoteSystemList {
	private:
		struct VoteList {District* d;VoteSystem *v;Party* winParty;};
		Result* res;
		myLST<VoteList>voteSysListPerDistrict;
		int sizeList;
	public:
		VoteSystemList();
		VoteSystemList(ifstream& infile);//פה לעכדן שדה גודל רשימה

		~VoteSystemList();
		void operator=( VoteSystemList& other);
		void addNode(District* d);
		void addNodeParty(Party* p);
		void updateVotes(int district, int party);
		void countVotes();
		void updatePrecentsInParty();
		void displayRegularElection();
		void displaySimpleElection();
		void buildRes(int, int, VoteSystem*);
		Result* getRes()const { return res; }
		void save(ofstream& out, bool flagElection);
		void updateSize();
		void createNodeList(District* d, VoteSystem& v, Party* p);
		myLST<VoteList> getList() { return voteSysListPerDistrict; }
		VoteSystem* getVoteSys();
		
	};

}
