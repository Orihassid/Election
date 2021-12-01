#pragma once
#include"voter_Register.h"
#include"district_Devide.h"
#include"district_Unit.h"
#include"party.h"
#include "voteSystemList.h"
#include <fstream>



namespace P {
	class Election{
	protected:
		struct Date { int day, month, year; };
		Date d;
		struct NodeDistrictList { District* d;};
		struct NodeResPartyList { Party* p; int numOfVotes; int numOfRepresentors;};
		struct NodePartyList { Party* p; int numOfVotes; int numOfRepresentors;
		bool operator>(NodePartyList& other);
		bool operator<(NodePartyList& other);
		};
		struct voteSystem_Node { VoteSystem* v; };


		myLST<NodePartyList>PartyList;
		myLST<NodeResPartyList>ResPartyList;
		myLST<NodeDistrictList>DistrictList;
		myLST<voteSystem_Node>newVoteSysList;


		int sizeDistrictList, sizePartyList, sizePartyResList;
		VoteSystemList voteList;

	public:
		Election(int _d, int _m, int _y)throw (string);
		Election(ifstream& infile, Voter_Register* v, bool flag);
		void operator=(Election& other);
		virtual ~Election();
		void addNodeToTailPartyList(Party& p);
		void displayDistricts();
		void displayPartys();
		void addNodeToTailDistrictList(District* d);
		void upadteParty(Citizen* c, int p, int d = 1);
		void addDistrictToPartyList();
		int getNumOfDistricts();
		District* findDistrict(int districtNumber);
		void addCitizenToDistrict(Voter_Register& v);
		void addNodeToVoteList();
		void addNodePartyPerDistrict();
		void updateVotes(Citizen* citizen);
		void displayResualt();
		void updatePrecentsInDistricts();
		void updatePrecentsInParty();
		virtual void display();
		void printResultPartyList();//להדפיס רשימה מקושרת שממויינת לפי מספר נציגים מכל מחוז , המפלגה המנצחת תיהיה ראש הרשימה 
		void buildPartyResList();
		void updatePartyVotesLinkedList(int partyNum);
		void updatePartyRepresentorsLinkList();
		void updateResult(int numElectors, int partySerialNumber);
		void addNodeToTailResList(NodePartyList* node);
		void updateResult2(VoteSystem& v);
		friend ostream& operator<<(ostream&, const Election&);
		virtual void toOs(ostream& os)const;
		void save(ofstream& out, bool flagElection);
		void updateSizes();
		void savePartyList(ofstream& out);
		void saveDistrictList(ofstream& out);
		void addVoteSystemToTail(VoteSystem* v);
		void saveVoteSystemList(ofstream& out);
		void loadDistrictList(ifstream& in, Voter_Register* v);
		void loadPartyList(ifstream& in, bool regular, Voter_Register* v);
		void addNodeToTailPartyListLoad(NodePartyList* node);
		void loadVoteSystemList(ifstream& infile, bool electionType);
		void loadLinkListVoteSys(ifstream& infile, bool electionType);
		Party* findPartyFromResParty(int partyId);
		Party* findPartyFromParty(int partyId);
		VoteSystem& findVoteSys(int index);
		void updateDistrictsInCitizens(Voter_Register* v);
		void addNodeToTailPartyList(NodeResPartyList* node);
		void refreshNumElectorsResultPartyList();
		VoteSystemList& getVoteList() {	return voteList;}
		myLST<NodeDistrictList> getDistrictList() { return DistrictList; }
		void clearResList();
		void getData();
		int getYear() { return d.year;};
		int getNumOfPartys() { return PartyList.size(); }
		static bool wasLoad;
	};


}