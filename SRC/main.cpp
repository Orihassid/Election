// Shalev Sharf 205738370
// Orie Hassid 209635903
#include <fstream>
#include "election_Simple.h"
#include "voter_Register.h"
#include "district_Devide.h"
#include "district_Unit.h"
#include "Strings.h"
using namespace std;
using namespace P;

void mainMenu2(Election& e, Voter_Register& v, Election* tempE=nullptr,bool afterLoad = false, bool isTempE = false);
void over18(int electionYear, int yearOfBirth);
void mainMenu2(Election& e, Voter_Register& v, Election* tempE, bool afterLoad, bool isTempE ){
	Election* tempECurr = tempE;
	Election* simpleElection = dynamic_cast<Election_Simple*>(&e);
	Voter_Register v2;
	string name;
	string districtName;
	string PartyName;
	string fileName;
	int input, id, yearOfBirth, districtNumber, partyNum, size, districtNum, simpleElector,electionYear;
	bool flagDistrict, flagElectionCurr, isTempECurr = isTempE, afterLoadCurr = afterLoad;
	District* defultDistrict = nullptr, * d;
	if (simpleElection) {
		
		cout << "enter num of electors for Simple Election";
		cin >> simpleElector;
		try {
			defultDistrict = new District_Devide("default", simpleElector);//אם הבחירות פשוטות נוצר רק מחוז מחולק דיפולטי יחידי
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		e.addNodeToTailDistrictList(defultDistrict);
		e.addDistrictToPartyList();
		e.addNodeToVoteList();
	}
	while (true) {
		cout << "1.Add district(name,number of electors,type-1:unit,0:divided)" << endl
			<< "2.Add citizen(name,id,year of birth,district number)" << endl
			<< "3.Add party(name,candidate id)" << endl
			<< "4.Add representor citizen(id,district number,party number)" << endl
			<< "5.Print all districts details(district number,name of district,number of electors)" << endl
			<< "6.Print all citizens details(name,id,year of birth,district number)" << endl
			<< "7.Print all parties details(name,party number,name of candidate,representors of each districts" << endl
			<< "8.Vote: add citizen id and number party " << endl
			<< "9.Print results elections" << endl
			<< "10.Exit " << endl
			<< "11.Save File (file name) " << endl
			<< "12.Load File (file name)  " << endl;
		cin >> input;
		if (isTempECurr) {
			e = *tempECurr;
			isTempECurr = false;
		}
		if (input < 1 || input>12)
		{
			cout << "Invalid input. Please try again" << endl;
			continue;
		}
		else {
			electionYear = e.getYear();
			if (input == 1) {
				if (simpleElection)
				{
					cout << "you chose simple election,there is no district to add" << endl;

				}
				else {

					cin >> districtName >> size >> flagDistrict;
					while (size < 0) {
						cout << "wrong input size representive";
						cin >> size;
					}
					if (flagDistrict) {
						try {
							d = new District_Unit(districtName, size);
							e.addNodeToTailDistrictList(d);
							e.addDistrictToPartyList();
							e.addNodeToVoteList();
						}
						catch (bad_alloc & ex)
						{
							cout << ex.what();
							exit(1);
						}
						catch (string msg) {
							cout << msg << endl;
						}	
					}
					else {
						try {
							d = new District_Devide(districtName, size);
							e.addNodeToTailDistrictList(d);
							e.addDistrictToPartyList();
							e.addNodeToVoteList();
						}
						catch (bad_alloc & ex)
						{
							cout << ex.what();
							exit(1);
						}
						catch (string msg) {
							cout << msg << endl;
						}
					}
				}
				continue;
			}
			else if (input == 2) {
				cin >> name >> id;
					while (id < 100000000 || id>999999999)
					{
						cout << "the id should be 9 digits!!" << endl;
						cout << "please enter valid id: ";
						cin >> id;
					}
					cin >> yearOfBirth>> districtNumber;

				// אם הבחירות פשוטות נשלח ישר לבנאי של אזרח מצביע למחוז המחולק הדיפולטיבי שקיים
				if (simpleElection) {
					try {
						Citizen c(name, id, yearOfBirth, defultDistrict);
						over18(electionYear, yearOfBirth);
						v.addNodeToTail(c);
						e.addCitizenToDistrict(v);
						if (afterLoadCurr) {
							auto itr = e.getDistrictList().begin();
							itr->d->addCitizenToTail(&c);
						}
					}
					catch(string msg){
						cout << msg<<endl;
					}
				}
				else {
					d = e.findDistrict(districtNumber);
					try {
						Citizen c(name, id, yearOfBirth, d);
						over18(electionYear, yearOfBirth);
						v.addNodeToTail(c);
						e.addCitizenToDistrict(v);
 					}
					catch (string msg) {
						cout << msg << endl;
						
					}
				}
				continue;

			}
			else if (input == 3) {
				cin >> PartyName >> id;
				Citizen* c = v.candidateParty(id);
				int numofDistricts;
				numofDistricts = e.getNumOfDistricts();

				if (c != nullptr) {
					Party p(PartyName, id, c, numofDistricts);
					e.addNodeToTailPartyList(p);
					e.addNodePartyPerDistrict();
				}
				else {
					cout << "Invalid id please try again" << endl;
				}
				continue;
			}
			else if (input == 4) {
				cin >> id >> districtNum >> partyNum;
				Citizen* citizen = nullptr;
				while (partyNum > e.getNumOfPartys()) {
					cout << "invalid party id number" << endl << "pls enter party id" << endl;
					cin >> partyNum;
				}
				if (simpleElection) {
					//ניתן הנחיה של להתעלם מהקלט של districtNum
					if (v.updateCitizen(id, &citizen)) {
						e.upadteParty(citizen, partyNum);
					}
				}
				else {
					if (v.updateCitizen(id, &citizen)) {
						e.upadteParty(citizen, partyNum, districtNum);
					}
				}
				continue;
			}
			else if (input == 5) {
				if (simpleElection) {
					cout << "you chose simple election,there is no district to display" << endl;
				}
				else {
					e.displayDistricts();
				}
				continue;
			}
			else if (input == 6) {
				v.displayCitizens();
				continue;
			}
			else if (input == 7) {
				e.displayPartys();
				continue;
			}
			else if (input == 8) {
				cin >> id >> partyNum;
				Citizen* citizen = nullptr;
				while (partyNum > e.getNumOfPartys()) {
					cout << "invalid party id number" << endl << "pls enter party id" << endl;
					cin >> partyNum;
				}
				try {
					citizen = v.vote(partyNum, id);
					e.updateVotes(citizen);
				}
				catch (string msg){
					cout << msg << endl;
				}
				catch (bool flag) {
					cout << "Invalid id" << endl;
				}
				continue;
			}
			else if (input == 9) {
				cout << "**********************************RESULTS**************************************:" << endl; \
				cout << e;
				e.displayResualt();
				e.updateSizes();

				continue;
			}
			else if (input == 10) {
			cout << "GOOD BYE!" << endl;
				break;
			}
			else if (input == 11) {
				cin >> fileName;
				ofstream outfile(fileName, ios::binary | ios::trunc);
				if (!outfile.good()) {
					cout << "Error reading" << endl;
					exit(-1);
				}
				if (simpleElection) {
					flagElectionCurr = false;				
					e.getData();

				}
				else {
					flagElectionCurr = true;
				}
				outfile.write(rcastcc(&flagElectionCurr), sizeof(bool));

				v.save(outfile);
				e.save(outfile, flagElectionCurr);
				outfile.close();

				continue;
			}
			else if (input == 12) {
				cin >> fileName;
				ifstream infile(fileName, ios::binary);
				if (!infile.good()) {
					cout << "Error reading" << endl;
					exit(-1);
				}
				infile.read(rcastc(&flagElectionCurr), sizeof(bool));
				Voter_Register* tempVoter;
				
				try {
					tempVoter = new Voter_Register(infile);

				}
				catch (bad_alloc & ex)
				{
					cout << ex.what();
					exit(1);
				}
				v = *tempVoter;

				
				if (flagElectionCurr) {//election type for dynamic cast
					try {
						tempECurr = new Election(infile, tempVoter, flagElectionCurr);
						e.wasLoad = true;
					}
					catch (bad_alloc & ex)
					{
						cout << ex.what();
						exit(1);
					}
				}
				else {
					try {
						tempECurr = new Election_Simple(infile, tempVoter, flagElectionCurr);
					}
					catch (bad_alloc & ex)
					{
						cout << ex.what();
						exit(1);
					}
				}
				isTempECurr = true;
				afterLoadCurr = true;
				infile.close();
				continue;
				}
			}
		}
	}
	
void mainMenu() {
	Voter_Register v;
	Election* e =nullptr,*tempE;
	int day, month, year, input;
	string fileName;
	bool flagElection, isTempE,afterLoad;

	while (true) {
		cout << "1.please enter Date: Day,Month,Year:, and type of election (0 = simple,1 = regular)" << endl
			<< "2. enter - name of file" << endl
			<< "3.exit" << endl;

		cin >> input;
		if (input == 1) {
			cin >> day >> month >> year >> flagElection;
			if (flagElection) {
				try {
					e = new Election(day, month, year);
				}
				
				catch (bad_alloc & ex)
				{
					cout << ex.what();
					exit(1);
				}
				catch (string msg) {
					cout << msg << endl;
					continue;
				}
			}
			else {
				try {
					e = new Election_Simple(day, month, year);
				}
				catch (bad_alloc & ex)
				{
					cout << ex.what();
					exit(1);
				}
			}
			mainMenu2(*e, v);
		}
		else if (input == 2) {
			cin >> fileName;
			ifstream infile(fileName, ios::binary);
			if (!infile.good()) {
				cout << "Error reading" << endl;
				exit(-1);
			}
			infile.read(rcastc(&flagElection), sizeof(bool));
			Voter_Register* tempVoter;
			try {
				tempVoter = new Voter_Register(infile);
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			v= *tempVoter;

			if (flagElection) { //election type for dynamic cast
				try {
					tempE = new Election(infile, tempVoter, flagElection);

				}
				catch (bad_alloc & ex)
				{
					cout << ex.what();
					exit(1);
				}
			}
			else {
				try {
					tempE = new Election_Simple(infile, tempVoter, flagElection);
				}
				catch (bad_alloc & ex)
				{
					cout << ex.what();
					exit(1);
				}
			}
			isTempE = true;
			//afterLoad = true;
			afterLoad = false;

			mainMenu2(*tempE, v, tempE, isTempE, afterLoad);
			infile.close();
		}
		else if (input == 3) {
			cout << "goodbye !!!" << endl;
			break;
		}
		else {

			continue;
		}
	}
}
void over18(int electionYear, int yearOfBirth) {
	if ((electionYear - yearOfBirth) < 18) {
		string msg;
		msg = "citizen is only above 18. press 2 and enter citizen details again: ";

		throw(msg);
	}
}
int main() {
	
	mainMenu();
}







