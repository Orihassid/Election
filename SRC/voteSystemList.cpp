#include "voteSystemList.h"

namespace P {

	VoteSystemList::VoteSystemList() {
	voteSysListPerDistrict.init();
	}

	VoteSystemList::VoteSystemList(ifstream& infile)
	{

	}

	VoteSystemList::~VoteSystemList() {

	}

	void VoteSystemList::operator=( VoteSystemList& other) {
		this->sizeList = other.sizeList;
		this->res = other.res;


		voteSysListPerDistrict.clear();
		auto itr = other.voteSysListPerDistrict.begin();
		auto end= other.voteSysListPerDistrict.end();
		VoteList* curr=nullptr;
		for (; itr != end; itr++) {
			try {
				curr = new VoteList{ itr->d,itr->v,itr->winParty };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			voteSysListPerDistrict.push_Back(*curr);
		}
	
	}

	void VoteSystemList::addNode(District* d) {

		VoteSystem* vs = nullptr;
		VoteList* temp = nullptr;
		try {
			vs = new VoteSystem;
			temp = new VoteList{ d,vs,nullptr };
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		voteSysListPerDistrict.push_Back(*temp);
	}

	void VoteSystemList::addNodeParty(Party* p) {
		int index;
		VoteSystem* v1 = nullptr;  
		auto itr = voteSysListPerDistrict.begin();
		auto end = voteSysListPerDistrict.end();
		
		for (; itr != end; itr++) {
			v1 = itr->v;
			v1->getSizeFromList(&index);
			if(p->getSerialNumber()> (index))
			itr->v->addPartyNodeToTail(p);
		}
	}
	void VoteSystemList::updateVotes(int districtNum, int partyNum) {
		auto itr = voteSysListPerDistrict.begin();
		while (districtNum > 1) {
			districtNum--;
			itr++;
		}
		itr->v->updatePartyVote(partyNum);
	}
	void VoteSystemList::countVotes() {
		auto itr = voteSysListPerDistrict.begin();
	
		int size = voteSysListPerDistrict.size();
		int numOfVotes;
		for (int i = 0; i < size;i++) {
			numOfVotes = itr->v->countVotes();
			itr->d->setVoteNum(numOfVotes);
			itr++;
		}
	}

	void VoteSystemList::updatePrecentsInParty() {
		auto itr = voteSysListPerDistrict.begin();

		int size = voteSysListPerDistrict.size();
		int voteNum;
		for (int i = 0; i < size; i++) {
			voteNum = itr->d->getvoteNum();
			itr->v->setDistrictVotes(voteNum);
			itr->v->updatePrecents();
			itr++;
		}
	}

	void VoteSystemList::displayRegularElection() {
		auto itr = voteSysListPerDistrict.begin();
		auto itr2 = voteSysListPerDistrict.begin();
		itr2++;
		auto end = voteSysListPerDistrict.end();
		District* curr_district = itr->d;
		Party* party;
		try {
			this->res = new Result;
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		int numElectors, partySerialNum;
		for (; itr != end; itr++, itr2++) {//רץ על מחוזות
			cout << *(itr->d) << endl;//הדפסת מספר מחוז שם ומספר אלקטורים

			curr_district = dynamic_cast<District_Unit*>(curr_district);
			party = itr->v->getWinParty();//מצביע למפלגה המנצחת
			itr->winParty = party;


			if (party) {
				itr->v->displayRegular(*(itr->d));//לכל מפלגה שקיבלה לפחות נציג אחד נדפיס את המועמד ונציגיה, בנוסף נדפיס את הפרטים של המפלגות

				if (curr_district) {//אם המחוז מאוחד

					numElectors = itr->d->getNumOfelctors();
					partySerialNum = itr->winParty->getSerialNumber();
					buildRes(numElectors, partySerialNum, (itr->v));
				}
				else {

					buildRes(0, 0, (itr->v));

				}
			}
			else {
				cout << "At this distirct there are no votes!" << endl << endl;
			}
			cout << "Percentage vote at this district are: " << itr->d->getPrecentOfVoters() << "%" << endl << endl << endl;//מדפיס את אחוז ההצבעה במחוז
			cout << "-----------------------" << endl;


			if (itr2 != end)
				curr_district = itr2->d;

		}
	}

	void VoteSystemList::displaySimpleElection() {
		auto itr = voteSysListPerDistrict.begin();
		District_Devide* curr_district = (District_Devide*)itr->d;//המחוז הדיפולטיבי מחולק
		Party* party;
		cout << "Percentage vote at this Election are: " << itr->d->getPrecentOfVoters() << "%" << endl << endl << endl;//מדפיס את אחוז ההצבעה במחוז
		party = itr->v->getWinParty();//מצביע למפלגה המנצחת
		itr->winParty = party;
		if (party) {
			itr->v->displaySimple(*(itr->d));//נדפיס את המועמד ונציגיה, בנוסף נדפיס את הפרטים של המפלגות
		}
		else {
			cout << "At this distirct there are no votes!" << endl << endl;
		}


	}

	void VoteSystemList::buildRes(int numElectors, int partyNum, VoteSystem* _v) {
		this->res->addToTail(numElectors, partyNum, _v);
	}

	void VoteSystemList::save(ofstream& out, bool regular) {
		auto itr = voteSysListPerDistrict.begin();
		int districtId, partyId;

		updateSize();
		for (int i = 0; i < sizeList; i++) {
			districtId = itr->d->getSerialNumber();
			out.write(rcastcc(&districtId), sizeof(int));
			itr->v->save(out);
			partyId = itr->winParty->getSerialNumber();
			out.write(rcastcc(&partyId), sizeof(int));
			itr++;
		}
	}


	void VoteSystemList::updateSize() {
		sizeList = voteSysListPerDistrict.size();
	}

	void VoteSystemList::createNodeList(District* d, VoteSystem& v, Party* p)
	{

		VoteList* curr2;
		v.wasLoad = true;

		VoteList* curr = nullptr;
		try {
		curr=new VoteList{ d,&v,p };
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}

		voteSysListPerDistrict.push_Back(*curr);
	}

	VoteSystem* VoteSystemList::getVoteSys(){
		auto itr = voteSysListPerDistrict.begin();
		
		return itr->v;
	}

}
