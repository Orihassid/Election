#include "VoteSystem.h"
namespace P {

	int VoteSystem::counter2 = 0;
	bool VoteSystem::wasLoad = false;

	VoteSystem::VoteSystem() {
		districtVotes = 0;
		sizeList = 0;
		this->serialNumber = ++counter2;
	}

	VoteSystem::VoteSystem(VoteSystem& other) {
		*this = other;

	}
	VoteSystem::VoteSystem(VoteSystem& other, bool fromFile) {
		auto itr = other.NodeVoteList.begin();
		auto end = other.NodeVoteList.end();
		this->districtVotes = other.districtVotes;
		this->sizeList = other.sizeList;
		this->serialNumber = other.serialNumber;

		NodeVote* curr;

		for (; itr != end; itr++) {
			try {
				curr = new NodeVote{ itr->party,itr->counter,itr->votePrecents,itr->numOfRepresentor };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			
			addNodeToTail(curr);
			sizeList++;
			
		}

	}

	VoteSystem::~VoteSystem()
	{

	}

	void VoteSystem::operator=(VoteSystem&other)
	{
		this->districtVotes = other.districtVotes;
		this->sizeList = other.sizeList;
		this->serialNumber = other.serialNumber;
		NodeVoteList.clear();
	    auto itr = other.NodeVoteList.begin();
		auto end = other.NodeVoteList.end();
		NodeVote* curr;
		if (wasLoad)
			sizeList = 0;

		for (; itr != end; itr++) {
			try {
				curr = new NodeVote{ itr->party,itr->counter,itr->votePrecents,itr->numOfRepresentor };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			addNodeToTail(curr);
		}
		
	}

	void VoteSystem::addPartyNodeToTail(Party* p) {
		
		NodeVote* node = nullptr;
		try {
			node = new NodeVote{ p,0 };
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		
		this->NodeVoteList.push_Back(*node);

	}
	void VoteSystem::updatePartyVote(int partyNum) {
		auto itr = NodeVoteList.begin();
		while (partyNum > 1) {
			partyNum--;
			itr++;
		}
		itr->counter = itr->counter + 1;
	}

	int VoteSystem::countVotes() {
		int voteNum = 0;
		auto itr = NodeVoteList.begin();
		auto end = NodeVoteList.end();
		for (; itr != end; itr++)
			voteNum += itr->counter;
		return voteNum;
	}

	bool VoteSystem::setDistrictVotes(const int districtVotes) {
		if (districtVotes >= 0) {
			this->districtVotes = districtVotes;
			return true;
		}
		return false;
	}
	void VoteSystem::updatePrecents() {
		auto itr = NodeVoteList.begin();
		auto end = NodeVoteList.end();
		float num1, num2;
		float p;
		for (; itr != end; itr++) {
			num1 = itr->counter;
			num2 = districtVotes;
			p = (num1 / num2);
			itr->votePrecents = p * 100;
		}
	}
	void VoteSystem::updateVoteSystemNodes(District& district) {
		auto itr = NodeVoteList.begin();
		auto end = NodeVoteList.end();
		float votesPerParty;
		int counter = 0, size;
		float* voteArr, * numRepresentorsArr;
		for (; itr != end; itr++) {
			counter++;
		}
		itr = NodeVoteList.begin();
		size = counter;
		try {
			voteArr = new float[size];
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		counter = 0;
		for (; itr != end; itr++) {
			votesPerParty = itr->counter;
			voteArr[counter] = votesPerParty;
			counter++;
		}
		numRepresentorsArr = updateRepresentorsPerParty(district.getNumOfelctors(), district.getvoteNum(), voteArr, size);
		updateNodeVote(numRepresentorsArr, size);

		delete numRepresentorsArr;
	}
	Party* VoteSystem::getWinParty() {
		auto itr = NodeVoteList.begin();
		auto end = NodeVoteList.end();
		Party* party = itr->party;
		int max = 0, voteNum = 0;
		for (; itr != end; itr++) {
			voteNum = itr->counter;
			if (voteNum > max) {
				max = voteNum;
				party = itr->party;
			}
		}
		
		return party;
	}

	int VoteSystem::CompareRepresentors(const void* a, const void* b) {
		NodeVote* _a = *(NodeVote**)a;
		NodeVote* _b = *(NodeVote**)b;
		if ((_a->numOfRepresentor) > (_b->numOfRepresentor)) {
			return -1;

		}
		else if ((_a->numOfRepresentor) < (_b->numOfRepresentor)) {
			return 1;

		}
		else if ((_a->party->getSerialNumber()) < (_b->party->getSerialNumber())) {

			return 0;
		}
	}

	int VoteSystem::CompareVotes(const void* a, const void* b)
	{
		NodeVote* _a = *(NodeVote**)a;
		NodeVote* _b = *(NodeVote**)b;
		if ((_a->counter) > (_b->counter)) {
			return -1;

		}
		else if ((_a->counter) < (_b->counter)) {
			return 1;

		}
		else if ((_a->party->getSerialNumber()) < (_b->party->getSerialNumber())) {

			return 0;
		}
	}


	void VoteSystem::displayRegular(District& d) {
		auto itr = NodeVoteList.begin();
		auto end = NodeVoteList.end();
		NodeVote* curr;
		NodeVote** arr;
		Party* p;
		District* district;
		int size = 0, i = 0;
		for (; itr != end; itr++)
			size++;
		try {
			arr = new NodeVote * [size];
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		updateVoteSystemNodes(d);
		itr = NodeVoteList.begin();
		for (; itr != end; itr++) {
			try {
				curr = new NodeVote{ itr->party,itr->counter,itr->votePrecents,itr->numOfRepresentor };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			arr[i] = curr;
			i++;

		}
		qsort(arr, size, sizeof(NodeVote*), CompareRepresentors);
		district = dynamic_cast<District_Unit*>(&d);
		if (district) {
			p = arr[0]->party;
			cout << "Candidate:  " << p->getCandidate()->getName() << endl;//מדפיס את המועמד
			displayPartyDetails(arr, size, d);

		}
		else {
			for (i = 0; i < size; i++) {
				p = arr[i]->party;
				if (arr[i]->numOfRepresentor >= 1) {
					cout << "Candidate:  " << p->getCandidate()->getName() << endl;//מדפיס את המועמד
					cout << "Party name:" << arr[i]->party->getName() << endl << "num of votes: " << arr[i]->counter << " , " << arr[i]->votePrecents << " %" << endl;
					cout << "num of representor: " << arr[i]->numOfRepresentor << endl << endl;
					printRepresentors(arr[i]->party, arr[i]->numOfRepresentor, i + 1);//שולח מספר נציגים,מצביע למפלגה,מספר מחוז
					cout << endl;
				}
				else {
					cout << "Party name:" << arr[i]->party->getName() << endl << "num of votes: " << arr[i]->counter << " , " << arr[i]->votePrecents << " %" << endl;
					cout << "num of representor: " << arr[i]->numOfRepresentor << endl;
					cout << endl;

				}
			}

		}
	}



	void VoteSystem::displaySimple(District& d) {
		auto itr = NodeVoteList.begin();
		auto end = NodeVoteList.end();
		NodeVote** arr;
		NodeVote* curr;
		Party* p;
		District* district;
		int size = 0, i = 0;
		for(;itr!=end;itr++)
			size++;
			
		arr = new NodeVote * [size];
		updateVoteSystemNodes(d);
		itr = NodeVoteList.begin();
		for (; itr != end; itr++) {
			try {
				curr = new NodeVote{ itr->party,itr->counter,itr->votePrecents,itr->numOfRepresentor };
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			arr[i] = curr;
				i++;
		}
		qsort(arr, size, sizeof(NodeVote*), CompareVotes);
		for (i = 0; i < size; i++) {
			p = arr[i]->party;
			cout << "Candidate:  " << p->getCandidate()->getName() << endl;//מדפיס את המועמד
			cout << "Party name:" << arr[i]->party->getName() << endl << "num of votes: " << arr[i]->counter << " , " << arr[i]->votePrecents << " %" << endl;
			cout << "num of representor: " << arr[i]->numOfRepresentor << endl << endl;
			printRepresentors(arr[i]->party, arr[i]->numOfRepresentor, 1);//שולח מספר נציגים,מצביע למפלגה,מספר מחוז
			cout << endl;

		}
	}

	void VoteSystem::displayRepresentors(Party* p, int numElectors, int districtNum) {
		p->getList().displayRepresents(numElectors, districtNum);
	}
	float* VoteSystem::updateRepresentorsPerParty(int numOfelctors, int voteNum, float* arr, float size) {
		float* res = nullptr;
		try {
			res = new float[size];
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		for (int c = 0; c < size; c++) {
			res[c] = 0;
		}
		float elector = voteNum / numOfelctors;
		int maxIndex = 0, max = 0;
		for (int i = 0; i < numOfelctors; i++) {
			for (int j = 0; j < size; j++) {
				if (arr[j] > max) {
					max = arr[j];
					maxIndex = j;
				}
			}
			arr[maxIndex] = arr[maxIndex] - elector;
			res[maxIndex]++;
			max = 0;
			maxIndex = 0;
		}
		delete[]arr;
		return res;

	}


	void VoteSystem::printRepresentors(Party* p, int numRepresentors, int numDistrict) {
		p->getList().displayRepresents(numRepresentors, numDistrict);
	}
	void VoteSystem::updateNodeVote(float* arr, int size) {
		auto itr = NodeVoteList.begin();
		auto end = NodeVoteList.end();
		int i = 0;
		for (; itr != end; itr++) {
			itr->numOfRepresentor = arr[i];
			i++;
		}
	}

	void VoteSystem::displayPartyDetails(NodeVote** arr, int size, District& d) {
		for (int i = 0; i < size; i++) {
			cout << "Party name:" << arr[i]->party->getName() << endl << "num of votes: " << arr[i]->counter << " , " << arr[i]->votePrecents << " %" << endl;
			cout << "num of representor: " << arr[i]->numOfRepresentor << endl;
			cout << endl;
			displayRepresentors(arr[i]->party, d.getNumOfelctors(), d.getSerialNumber());
		}
	}
	void VoteSystem::save(ofstream& out)
	{
		auto itr = NodeVoteList.begin();
		int partyId,sizeNodeVoteList;
		sizeList = NodeVoteList.size();
		out.write(rcastcc(&districtVotes), sizeof(float));
		out.write(rcastcc(&sizeList), sizeof(int));
		out.write(rcastcc(&serialNumber), sizeof(int));
		
		for (int i = 0; i < sizeList; i++)
		{
			partyId = itr->party->getSerialNumber();
			out.write(rcastcc(&(partyId)), sizeof(int));
			out.write(rcastcc(&(itr->counter)), sizeof(int));
			out.write(rcastcc(&(itr->votePrecents)), sizeof(float));
			out.write(rcastcc(&(itr->numOfRepresentor)), sizeof(int));
			itr++;
		}

	}
	VoteSystem::VoteSystem(ifstream& in) {
		in.read(rcastc(&districtVotes), sizeof(float));
		in.read(rcastc(&sizeList), sizeof(int));
		in.read(rcastc(&serialNumber), sizeof(int));
	}
	void VoteSystem::LoadVote(ifstream& in)
	{
		in.read(rcastc(&districtVotes), sizeof(float));
		in.read(rcastc(&sizeList), sizeof(int));
		in.read(rcastc(&serialNumber), sizeof(int));
		int partyId, counter, numOfRepresentor;
		float votePrecents;
		for (int i = 0; i < sizeList; i++) {
			in.read(rcastc(&partyId), sizeof(int));
			in.read(rcastc(&counter), sizeof(int));
			in.read(rcastc(&votePrecents), sizeof(float));
			in.read(rcastc(&numOfRepresentor), sizeof(int));
		}
	}
	

	void VoteSystem::updateSize()
	{
		sizeList = NodeVoteList.size();

	}
	void VoteSystem::setNodeDetails(Party* p, int numVotesPerParty, float precentVote, int numElectors) {

		NodeVote* curr = nullptr;
		try {
			curr = new NodeVote{ p,numVotesPerParty ,precentVote ,numElectors };
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		NodeVoteList.push_Back(*curr);
	}
	void VoteSystem::addNodeToTail(NodeVote* node) {


		bool flag = wasLoad;

		if (NodeVoteList.empty()|| flag) {
			wasLoad = false;
			NodeVoteList.push_Back(*node);
		}
		else {
			NodeVoteList.push_Back(*node);
		}
	}
	
	void VoteSystem::getData(int index, int* numRepresentors)
	{
		auto itr = NodeVoteList.begin();

		for (int i = 0; i < index; i++)
			itr ++ ;
		*numRepresentors = itr->numOfRepresentor;


		
	}

	void VoteSystem::getSizeFromList(int*size){
		*size = NodeVoteList.size();
	}
	
}