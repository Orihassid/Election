#include "election.h"
#include <algorithm>
#include <iostream>

namespace P {
	using namespace std;
	
	bool Election::wasLoad = false;

	Election::Election(int _d, int _m, int _y) throw (string) : d{ _d,_m,_y }, voteList(), sizeDistrictList(0), sizePartyList(0), sizePartyResList(0){
		if (_y <= 0) {
			string msg = "invalid year";
			throw msg;
		}
		if (_d <= 0 || _d > 31) {
			string msg = "invalid day";
			throw msg;
		}
		if (_m <= 0 || _m > 12) {
			string msg = "invalid month";
			throw msg;
		}
		else if (_m == 2 && _d > 28) {
			string msg = "on ferbuary there is onty 28 days";
			throw msg;

		}

	}
	Election::Election(ifstream& infile, Voter_Register* v, bool electionType) : voteList() {
		//מתודה שמעדכנת את המצביע של המחוז בכל אזרח בפנקס הבוחרים
		infile.read(rcastc(&d), sizeof(d));
		loadDistrictList(infile, v);
		loadPartyList(infile, electionType, v);
		loadLinkListVoteSys(infile, electionType);
		loadVoteSystemList(infile, electionType);
		//אין טעינה
		updateDistrictsInCitizens(v);
	}
	void Election::operator=(Election& other) {
		this->d = other.d;
		this->sizeDistrictList = other.sizeDistrictList;
		this->sizePartyList = other.sizePartyList;
		this->sizePartyResList = other.sizePartyResList;
		this->voteList = other.voteList;
		this->newVoteSysList.clear();
		this->ResPartyList.clear();
		this->PartyList.clear();
		this->DistrictList.clear();
		auto itr = other.PartyList.begin();
		auto end = other.PartyList.end();
		NodePartyList* item = nullptr;
		for (; itr != end; itr++) {
			try {
				item = new NodePartyList{ itr->p,itr->numOfVotes ,itr->numOfRepresentors };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			PartyList.push_Back(*item);
		}


		auto itr2 = other.DistrictList.begin();
		auto end2 = other.DistrictList.end();
		NodeDistrictList* curr = nullptr;
		for (; itr2 != end2; itr2++) {
			try {
				curr = new NodeDistrictList{ itr2->d };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			DistrictList.push_Back(*curr);
		}
	}
	Election::~Election() {}




	void Election::upadteParty(Citizen* citizen, int partyNum, int districtNum) {
		auto itr = PartyList.begin();
		
		while (partyNum > 1) {
			itr++;
			partyNum--;
		}
		itr->p->getList().addRepresentor(citizen, districtNum);
	}

	void Election::addDistrictToPartyList() {
		auto itr = PartyList.begin();
		auto end = PartyList.end();
		for(;itr!=end;itr++) {
			itr->p->getList().addNode(1);//we add one node  
			
		}

	}

	int Election::getNumOfDistricts(){
		auto itr = DistrictList.begin();
		auto end = DistrictList.end();
		int counter = 0;
		for (; itr != end; itr++) {
			counter++;	
		}
		return counter;
	}

	District* Election::findDistrict(int districtNumber){
		auto itr = DistrictList.begin();
		while (districtNumber > 1) {
			itr++;
			districtNumber--;
		}

		return itr->d;
	}

	void Election::addCitizenToDistrict(Voter_Register& v) {
		Citizen* citizen = v.getCitizen();
		District* district = citizen->getDistrict();
		District* temp = dynamic_cast<District_Unit*>(district);
		if (temp) {

			temp->addCitizenToTail(citizen);
		}
		else {
			temp = dynamic_cast<District_Devide*>(district);
			if (temp)
				temp->addCitizenToTail(citizen);
		}

	}

	void Election::addNodeToVoteList() {
		auto itr = DistrictList.begin();
		auto itr2 = DistrictList.begin();
		itr2++;
		auto end = DistrictList.end();
		District* d = nullptr;
		for (; itr != end; itr++, itr2++) {
		if (!(itr2 != end))
			d = itr->d;
		}
		voteList.addNode(d);
		
		
	}

	void Election::addNodePartyPerDistrict() {
		Party* party = nullptr;
		if (!wasLoad) {
			auto itr = PartyList.begin();
			auto itr2 = PartyList.begin();
			itr2++;
			auto end = PartyList.end();
			for (; itr != end; itr++, itr2++) {
				if (!(itr2 != end))
					party = itr->p;
			}
			voteList.addNodeParty(party);
		}
		else {
			auto itr = PartyList.begin();
			auto end = PartyList.end();
			for (; itr != end; itr++) {
				party = itr->p;
				voteList.addNodeParty(party);
			}
			

		}
	}

	void Election::updateVotes(Citizen* citizen) {
		int partyNum = citizen->getChosenParty();
		updatePartyVotesLinkedList(partyNum);//מעדכן בזמן אמת הצבעות למפלגה 
		voteList.updateVotes(citizen->getDistrict()->getSerialNumber(), citizen->getChosenParty());
	}

	void Election::displayResualt() {
		voteList.countVotes();
		updatePrecentsInDistricts();
		updatePrecentsInParty();
		display();
	}

	void Election::updatePrecentsInDistricts(){
		NodeDistrictList* curr;
		float num;
		float num2;
		float result;
		auto itr = DistrictList.begin();
		auto end = DistrictList.end();
		District* d;
		for (; itr != end; itr++) {
			num = itr->d->getvoteNum();
			num2 = itr->d->getCounterPeople();
			if (num2 != 0)
				result = (num / num2) * 100;
			else
				result = 0;
			itr->d->setPrecentOfVoters(result);
		}

	}

	void Election::updatePrecentsInParty() {
		voteList.updatePrecentsInParty();

	}

	void Election::display() {

		voteList.displayRegularElection();
		updatePartyRepresentorsLinkList();
		buildPartyResList();
		printResultPartyList();
		refreshNumElectorsResultPartyList();

	}

	void Election::printResultPartyList() {
		int size = PartyList.size();
		auto itr = ResPartyList.begin();
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "FINAL RESULTS:" << endl;
		for (int i =0;i<size;i++,itr++) {
			cout << endl << endl << endl;
			cout << itr->p->getName() << " - " << endl << endl;
			cout << itr->p->getCandidate()->getName() << ":  " << "num of representors : " << itr->numOfRepresentors << ", num of votes : " << itr->numOfVotes << endl;

		}
		cout << endl << endl << endl;
	}

	void Election::buildPartyResList() {
		auto itr = PartyList.begin();
		auto end = PartyList.end();
		NodeResPartyList* node;
		for (; itr != end; itr++) {
			try {
				node = new NodeResPartyList{ itr->p,itr->numOfVotes,itr->numOfRepresentors };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			ResPartyList.push_Back(*node);
		}

		bool sorted = false;
		while (!sorted)
		{
			sorted = true;
			if (PartyList.size() < 2) break;
			myLST<NodeResPartyList>::iterator iter = ResPartyList.begin();
			myLST<NodeResPartyList>::iterator iter_prev = ResPartyList.begin();
			iter++;
			while (iter != ResPartyList.end())
			{
				if ((*iter).numOfRepresentors > (*iter_prev).numOfRepresentors) {
					sorted = false;
					NodeResPartyList temp = (*iter);
					(*iter) = (*iter_prev);
					(*iter_prev) = temp;
				}
				else if (((*iter).numOfRepresentors == (*iter_prev).numOfRepresentors) && ((*iter).p->getSerialNumber() < (*iter_prev).p->getSerialNumber())) {
					sorted = false;
					NodeResPartyList temp = (*iter);
					(*iter) = (*iter_prev);
					(*iter_prev) = temp;
				}


				iter++;
				iter_prev++;
			}


		}
	}

	void Election::updatePartyVotesLinkedList(int partyNum) {
		auto itr = PartyList.begin();
		while (partyNum > 1) {
			partyNum--;
			itr++;
		}
		itr->numOfVotes++;
	}

	void Election::updatePartyRepresentorsLinkList() {
		int partySerialNumber;
		int numElectors;
		VoteSystem* voteSystem = nullptr;
		Result* res = nullptr;
		res = voteList.getRes();
		sizePartyList=PartyList.size();

		
		for (int i = 0;i< sizePartyList;i++) {
			
			res->getData(&numElectors, &partySerialNumber, &voteSystem,i);
			addVoteSystemToTail(voteSystem);
			//אם הוא מחולק
			if (numElectors == 0 || partySerialNumber == 0) {

				updateResult2(*voteSystem);
			}
			else {
				//אם הוא אחיד
				updateResult(numElectors, partySerialNumber);
			}
		}
		res->getList().clear();
	}
	void Election::updateResult(int numElectors, int partySerialNumber)
	{
		auto itr = PartyList.begin();
		while (partySerialNumber > 1) {
			partySerialNumber--;
			itr++;
		}
		itr->numOfRepresentors = itr->numOfRepresentors + numElectors;
	}
	void Election::addNodeToTailResList(NodePartyList* node) {
		NodeResPartyList* item = nullptr;
		try {
			item = new NodeResPartyList;
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		item->numOfRepresentors = node->numOfRepresentors;
		item->numOfVotes = node->numOfVotes;
		item->p = node->p;
		delete node;
		ResPartyList.push_Back(*item);
		
	}

	void Election::updateResult2(VoteSystem& v) {
		auto itr = PartyList.begin(); 
		auto end = PartyList.end();
		int i = 0, numRepresentors = 0;
		 for (; itr != end; itr++,i++) {
			 v.getData(i, &numRepresentors);
			 itr->numOfRepresentors += numRepresentors;
			
		 }
		 v.getList().clear();
	}

	void Election::toOs(ostream& os) const {
		os << "Regular Election " << endl;
	}


	void Election::save(ofstream& out, bool flagElection) {

		out.write(rcastcc(&d), sizeof(d));
		saveDistrictList(out);
		savePartyList(out);
		saveVoteSystemList(out);
		voteList.save(out, flagElection);
	}

	void Election::updateSizes() {
		sizeDistrictList = DistrictList.size();
		sizePartyList = PartyList.size();
		sizePartyResList = ResPartyList.size();	
	}

	void Election::savePartyList(ofstream& out) {
		auto itr = PartyList.begin();
		out.write(rcastcc(&sizePartyList), sizeof(sizePartyList));
		for (int i = 0; i < sizePartyList; i++) {
			itr->p->save(out);
			//להעתיק מספר הצבעות
			out.write(rcastcc(&(itr->numOfVotes)), sizeof(int));
			//להעתיק מספר נציגים
			out.write(rcastcc(&(itr->numOfRepresentors)), sizeof(int));
			itr++;
		}

	}

	void Election::saveDistrictList(ofstream& out) {
		auto itr = DistrictList.begin();
		bool flag;
		District* temp;
		out.write(rcastcc(&sizeDistrictList), sizeof(sizeDistrictList));
		for (int i = 0; i < sizeDistrictList; i++) {
			temp = dynamic_cast<District_Unit*>(itr->d);
			if (temp)
				flag = true;
			else
				flag = false;
			out.write(rcastcc(&flag), sizeof(bool));
			itr->d->save(out);
			itr++;
		}
	}

	void Election::addVoteSystemToTail(VoteSystem* v) {
		// create new item and set as tail of list
		voteSystem_Node* item = nullptr;
		try {

			item = new voteSystem_Node{ new VoteSystem(*v) };
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		newVoteSysList.push_Back(*item);
	}

	void Election::saveVoteSystemList(ofstream& out) {

		auto itr = newVoteSysList.begin();
		for (int i = 0; i < DistrictList.size(); i++) {
			itr->v->save(out);
			itr++;
		}
	}

	void Election::loadDistrictList(ifstream& in, Voter_Register* v)
	{
		
		NodeDistrictList* curr;
		District* dU = nullptr;
		District* dV;
		bool flag;
		int sizeArr, * arr = nullptr;
		Citizen* c;

		in.read(rcastc(&sizeDistrictList), sizeof(sizeDistrictList));
		//אם המחוז מאוחד
		for (int i = 0; i < sizeDistrictList; i++) {
			in.read(rcastc(&flag), sizeof(bool));
			if (flag) {//אם המחוז מאוחד {
				try {
					dU = new District_Unit(in, v, &sizeArr, &arr);
				}
				catch (bad_alloc & ex)
				{
					cout << ex.what();
					exit(1);
				}
				for (int j = 0; j < sizeArr; j++) {
					v->updateCitizen(arr[j], &c);
					dU->addCitizenToTail(c);
				}
				try {
					curr = new NodeDistrictList{ dU };
				}
				catch (bad_alloc & ex)
				{
					cout << ex.what();
					exit(1);
				}
				DistrictList.push_Back(*curr);
		
			}
			else {
				try {
					dV = new District_Devide(in, v, &sizeArr, &arr);
				}
				catch (bad_alloc & ex)
				{
					cout << ex.what();
					exit(1);
				}
				for (int j = 0; j < sizeArr; j++) {
					v->updateCitizen(arr[j], &c);
					dV->addCitizenToTail(c);
				}
				try {
					curr = new NodeDistrictList{ dV };
				}
				catch (bad_alloc & ex)
				{
					cout << ex.what();
					exit(1);
				}
				DistrictList.push_Back(*curr);
					
			}
		}
	}



	void Election::loadPartyList(ifstream& in, bool regular, Voter_Register* v) {
		Party* party;
		int numRepresentors, numVotes;
		NodePartyList* curr;
		in.read(rcastc(&sizePartyList), sizeof(sizePartyList));
		for (int i = 0; i < sizePartyList; i++) {
			try {
				party = new Party(in, v);
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			in.read(rcastc(&numVotes), sizeof(int));
			in.read(rcastc(&numRepresentors), sizeof(int));
			try {
				curr = new NodePartyList{ party , numVotes,numRepresentors };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}PartyList.push_Back(*curr);
		}

	}




	void Election::addNodeToTailPartyListLoad(NodePartyList* node) {
		
		NodePartyList* item = nullptr;
		try {
			item = new NodePartyList;
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		item->numOfRepresentors = node->numOfRepresentors;
		item->numOfVotes = node->numOfVotes;
		item->p = node->p;
		PartyList.push_Back(*item);
	}
	void Election::loadVoteSystemList(ifstream& infile, bool electionType) {
		int districtId, partyId;
		District* d;
		Party* p;
		VoteSystem* voteSys = nullptr;
		int counter, numOfrepresentor;
		float votePrecents;
		updateSizes();
			for (int i = 0; i < sizeDistrictList; i++) {
				try {
					voteSys = new VoteSystem();
				}
				catch (bad_alloc & ex)
				{
					cout << ex.what();
					exit(1);
				}
				infile.read(rcastc(&districtId), sizeof(int));
				d = findDistrict(districtId);
				*voteSys = findVoteSys(i);
				voteSys->LoadVote(infile);
				infile.read(rcastc(&partyId), sizeof(int));
				p = findPartyFromParty(partyId);
				voteList.createNodeList(d, *voteSys, p);
			}
			
		
	}

	void Election::loadLinkListVoteSys(ifstream& infile, bool electionType) {
		voteSystem_Node* curr;
		VoteSystem* v;
		Party* p;
		int numVotesPerParty, partyId, numVotesDistrict, numElectors, sizeParty;
		float precentVote;

		sizeParty = sizePartyList;
		for (int i = 0; i < sizeDistrictList; i++) {
			try {
				v = new VoteSystem(infile);
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			if (!(v->getList().empty()))
				v->getList().clear();
			for (int j = 0; j < sizeParty; j++) {
				infile.read(rcastc(&partyId), sizeof(int));
				infile.read(rcastc(&numVotesPerParty), sizeof(int));
				infile.read(rcastc(&precentVote), sizeof(float));
				infile.read(rcastc(&numElectors), sizeof(int));
				p = findPartyFromParty(partyId);
				v->setNodeDetails(p, numVotesPerParty, precentVote, numElectors);
			}
			try {
				curr = new voteSystem_Node{ v };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			newVoteSysList.push_Back(*curr);

		}
	}

	Party* Election::findPartyFromResParty(int partyId)
	{
		auto itr = ResPartyList.begin();
		auto end =ResPartyList.end();
		for (; itr != end; itr++) {
			if (itr->p->getSerialNumber() == partyId)
				return itr->p;
		}
		return nullptr;
	}

	Party* Election::findPartyFromParty(int partyId){
		auto itr = PartyList.begin();
		auto end = PartyList.end();
		for (; itr!=end; itr++){
			if (itr->p->getSerialNumber() == partyId)
				return itr->p;
		}
		return nullptr;
	}

	VoteSystem& Election::findVoteSys(int index) {
		auto itr = newVoteSysList.begin();
		for (int i = 0; i < index; i++){
			itr++;
		}
		return *(itr->v);
	}

	void Election::updateDistrictsInCitizens(Voter_Register* v) {
		int districtId;
		District* district;
		
		for(int i=0;i<v->getSizeList();i++){
			
			v->getData(&districtId, i);
			district = findDistrict(districtId);
			v->setData(district,i);
		}
		v->getList().clear();
	}

	void Election::addNodeToTailPartyList(NodeResPartyList* node){
		sizePartyList++;

		NodePartyList* item = nullptr;
		try {
			item = new NodePartyList{ node->p ,node->numOfVotes ,node->numOfRepresentors };
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		PartyList.push_Back(*item);
	}

	void Election::refreshNumElectorsResultPartyList()
	{
		auto itr = PartyList.begin();
		auto end = PartyList.end();
		auto itr2 = ResPartyList.begin();
		auto end2 = ResPartyList.end();
		for(;itr!=end;itr++){
			itr->numOfRepresentors = 0;
		}
		for (; itr2 != end2; itr2++) {
			itr2->numOfRepresentors = 0;
		}
	}
	void Election::clearResList(){
		ResPartyList.clear();
	}
	void Election::getData(){
		VoteSystem* v;
		v = voteList.getVoteSys();
		addVoteSystemToTail(v);

	}
	void  Election::addNodeToTailPartyList(Party& p) {
		Party* party = nullptr;
		try {
		party = new Party(p);
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		NodePartyList node{ party, 0, 0 };
		PartyList.push_Back(node);
	}

	void Election::displayDistricts() {
		auto itr = DistrictList.begin();
		auto end = DistrictList.end();
		for(;itr!=end;itr++){
			cout << *(itr->d);	
		}
	}
	void Election::displayPartys()  {
		auto itr = PartyList.begin();
		auto end = PartyList.end();
		for (; itr != end; itr++) {
			cout << *(itr->p);
	
		}
	}

	void  Election::addNodeToTailDistrictList(District* d) {
		
		NodeDistrictList* node = nullptr;
		try {

			node = new NodeDistrictList{ d };
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		DistrictList.push_Back(*node);
	}
	ostream& operator<<(ostream& os, const Election& e) {
		e.toOs(os);
		os << "Election: " << e.d.day << " " << e.d.month << " " << e.d.year << endl << endl;
		return os;
	}
	bool Election::NodePartyList::operator>(NodePartyList& other){
		if (this->numOfRepresentors > other.numOfRepresentors) {
			return 1;
		}
		else if (this->numOfRepresentors == other.numOfRepresentors) {
			if (this->p->getSerialNumber() < other.p->getSerialNumber()) {
				return 1;
			}
		}else
			return 0;
	}
	bool Election::NodePartyList::operator<(NodePartyList& other){
		if (this->numOfRepresentors < other.numOfRepresentors) {
			return 1;
		}
		else if (this->numOfRepresentors == other.numOfRepresentors) {
			if (this->p->getSerialNumber() > other.p->getSerialNumber()) {
				return 1;
			}
		}
		else
			return 0;
	}


}