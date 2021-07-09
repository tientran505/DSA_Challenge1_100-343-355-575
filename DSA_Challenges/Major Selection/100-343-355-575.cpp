#include "struct.h"

void fullMajorResult(_Major* head, StudentList* failed) //The result of all Major
{
	std::ofstream fileName;
	fileName.open("Result.csv");
	_Major* curM = head;
	while (curM != nullptr) //Run through all the nodes in the major linked list
	{
		_Student* curS = curM->data.stuList.pHead;
		while (curS != nullptr) //Run through all the student nodes in the linked list
		{
			fileName << curS->data.studentID << "," << curS->data.lastName << "," << curS->data.firstName << "," << curS->data.regDate.day << "/" << curS->data.regDate.month << "/" << curS->data.regDate.year << ",";
			for (int i = 0; i < 6; i++)
			{
				fileName << curS->data.interest.desiredMajor[i] << ",";
			}
			fileName << curS->data.interest.desiredMajor[curS->data.interest.chosen] << "," << curS->data.interest.chosen + 1 << "," << curS->data.gpa.GPA_Foundation << "," << curS->data.gpa.GPA_All << std::endl;
			curS = curS->pNextStu;
		}
		curM = curM->pNextMajor;
	}
	//print out the failed one

	_Student* pRun = failed->pHead;
	while (pRun != nullptr)
	{
		fileName << pRun->data.studentID << "," << pRun->data.lastName << "," << pRun->data.firstName << "," << pRun->data.regDate.day << "/" << pRun->data.regDate.month << "/" << pRun->data.regDate.year << ",";
		for (int i = 0; i < 6; i++)
		{
			fileName << pRun->data.interest.desiredMajor[i] << ",";
		}
		fileName << "failed" << "," << " " << "," << pRun->data.gpa.GPA_Foundation << "," << pRun->data.gpa.GPA_All << std::endl;
		pRun = pRun->pNextStu;
	}
	fileName.close();
}

void resultOfOneStu(std::string ID, _Major* head, StudentList* failed) //The result of a specific student
{
	_Major* curM = head; 
	while (curM != nullptr)
	{
		_Student* curS = curM->data.stuList.pHead;
		while (curS!=nullptr && curS->data.studentID.compare(ID) != 0) //check if the student is in this major
		{
			curS = curS->pNextStu;
		}
		if (curS != nullptr)
		{
			std::cout << "Student ID:" << curS->data.studentID << std::endl;
			std::cout << "Student name:" << curS->data.lastName << " " << curS->data.firstName << std::endl;
			std::cout << "Register date:" << curS->data.regDate.day << "/" << curS->data.regDate.month << "/" << curS->data.regDate.year << std::endl;
			std::cout << "Interests:";
			for (int i = 0; i < 6; i++)
			{
				std::cout << curS->data.interest.desiredMajor[i] << " ";
			}
			std::cout << std::endl << "Result:" << curS->data.interest.desiredMajor[curS->data.interest.chosen] << " " << curS->data.interest.chosen + 1 << " " << std::endl;
			std::cout << "GPA Foundation:" << curS->data.gpa.GPA_Foundation << std::endl;
			std::cout << "GPA All:" << curS->data.gpa.GPA_All << std::endl;
			return;
		}
		else curM = curM->pNextMajor; //move to the next major if the student is not in this major
	}

	if (curM == nullptr) //if the student cant be found in the major linked list, it means that the student is failed all six interests, check the student in the firstly created linked list
	{
		_Student* pRun = failed->pHead;
		while (pRun!=nullptr && pRun->data.studentID.compare(ID) != 0)
		{
			pRun = pRun->pNextStu;
		}
		if (pRun != nullptr)
		{
			std::cout << "Student ID:" << pRun->data.studentID << std::endl;
			std::cout << "Student name:" << pRun->data.lastName << " " << pRun->data.firstName << std::endl;
			std::cout << "Register date:" << pRun->data.regDate.day << "/" << pRun->data.regDate.month << "/" << pRun->data.regDate.year << std::endl;
			std::cout << "Interests:";
			for (int i = 0; i < 6; i++)
			{
				std::cout << pRun->data.interest.desiredMajor[i] << ",";
			}
			std::cout << std::endl << "Result:" << "Failed" << std::endl;
			std::cout << "GPA Foundation:" << pRun->data.gpa.GPA_Foundation << std::endl;
			std::cout << "GPA All:" << pRun->data.gpa.GPA_All << std::endl;
			return;
		}
		else //if the student cant be found anywhere
		{
			std::cout << "Student is not existed" << std::endl;
			return;
		}
	}
}

void resultOfOneM(std::string shortName, _Major* head) //The result of one specific major
{
	_Major* curM = head;
	while (curM != nullptr && curM->data.shortName.compare(shortName) != 0)//find the wanted major
	{
		curM = curM->pNextMajor;
	}
	if (curM != nullptr)
	{
		std::ofstream fileName;
		fileName.open(shortName + ".csv");
		_Student* curS = curM->data.stuList.pHead;
		while (curS != nullptr) //run through all the student nodes in the list
		{
			fileName << curS->data.studentID << "," << curS->data.lastName << "," << curS->data.firstName << "," << curS->data.regDate.day << "/" << curS->data.regDate.month << "/" << curS->data.regDate.year << ",";
			for (int i = 0; i < 6; i++)
			{
				fileName << curS->data.interest.desiredMajor[i] << ",";
			}
			fileName << curS->data.interest.desiredMajor[curS->data.interest.chosen] << "," << curS->data.interest.chosen + 1  << "," << curS->data.gpa.GPA_Foundation << "," << curS->data.gpa.GPA_All << std::endl;
			curS = curS->pNextStu;
		}
		fileName.close();
	}
	else //if the major cant be found
	{
		std::cout << "Invalid shortname";
		return;
	}
}

int isFoundation(std::string str) { //0 foundation, 1 sub, 2 general, check the type of the courses
	std::string temp;

	temp = str;
	temp.erase(temp.begin() + 4, temp.end());
	if (temp == "CSC1") return 0;

	temp = str;
	temp.erase(temp.begin() + 3, temp.end());
	if (temp == "BAA") {
		if (str[str.length() - 2] == '1' || str[str.length() - 2] == '2' || str[str.length() - 2] == '3') return 1;
	}
	return 2;
}

bool operator > (GPA a, GPA b) { //compare two students for sorted
	if (a.GPA_Foundation > b.GPA_Foundation) return 1;
	if (a.GPA_Foundation < b.GPA_Foundation) return 0;
	if (a.GPA_All > b.GPA_All) return 1;
	if (a.GPA_All < b.GPA_All) return 0;
	if (a.credit_Accumulated > b.credit_Accumulated) return 1;
	return 0;
}

int compareIDStudent(std::string std1, std::string std2) { // return 1 if std1 > std2, 2 if std1 < std2, 0 if std1 == std2
	std::string tmp1 = std1;
	std::string tmp2 = std2;

	tmp1.erase(tmp1.begin(), tmp1.begin() + 2); //erase the first two characters of the ID
	tmp2.erase(tmp2.begin(), tmp2.begin() + 2);

	if (stoi(tmp1) < stoi(tmp2)) return 2; //compare the remaining characters of the ID
	else if (stoi(tmp1) > stoi(tmp2)) return 1;
	else return 0;
}

_Student* findStu(_Student* head, _Student* tail, std::string stuID) { //find the student with ID
	if (head->data.studentID == stuID) return head;
	if (tail->data.studentID == stuID) return tail;
	_Student* left = head;
	_Student* right = tail;
	while (left != right || left->pNextStu != right || left->pPreStu != right) {
		if (left->data.studentID == stuID) return left;
		else if (right->data.studentID == stuID) return right;
		left = left->pNextStu;
		right = right->pPreStu;
		if (left == nullptr || right == nullptr) return nullptr;
	}
	return nullptr;
}

StudentList* readGrading(std::string fileName) {//read file Grading and create a student linked list
	StudentList* stuList = nullptr;
	std::ifstream fileIn;
	fileIn.open(fileName, std::ios_base::in);

	if (!fileIn.is_open()) {
		std::cout << "Can't open\n";
		return nullptr;
	}

	stuList = new StudentList;
	std::string temp;
	//getline(fileIn, temp); // skip 1 row
	_Student* pCur = nullptr;

	while (!fileIn.eof()) {
		getline(fileIn, temp, ','); //skip first collumn
		getline(fileIn, temp, ',');

		if (temp == "") break;

		if (pCur == nullptr || pCur->data.studentID != temp) { //create new node
			if (stuList->pHead == nullptr) {
				pCur = new _Student;
				pCur->pNextStu = nullptr;
				pCur->pPreStu = nullptr;
				pCur->data.studentID = temp;
				//std::cout << "MSSV = " << pCur->data.studentID << std::endl;
				stuList->pHead = pCur;
				stuList->pTail = pCur;
			}

			else {
				if (pCur->data.gpa.credits_General + pCur->data.gpa.credits_Foundation == 0) pCur->data.gpa.GPA_All = 0;
				else pCur->data.gpa.GPA_All /= (pCur->data.gpa.credits_General + pCur->data.gpa.credits_Foundation);

				if (pCur->data.gpa.credits_Foundation == 0) pCur->data.gpa.GPA_Foundation = 0;
				else pCur->data.gpa.GPA_Foundation /= pCur->data.gpa.credits_Foundation;

				pCur = new _Student;
				pCur->pNextStu = nullptr;
				pCur->pPreStu = nullptr;
				pCur->data.studentID = temp;

				//	if (strcmp(stuList->pTail->data.studentID.c_str(), pCur->data.studentID.c_str()) < 0) {
				if (compareIDStudent(stuList->pTail->data.studentID, pCur->data.studentID) == 2) {// CurID >  tail.StudentID 
					stuList->pTail->pNextStu = pCur;
					pCur->pPreStu = stuList->pTail;
					stuList->pTail = pCur;
				}

				//	else if (strcmp(stuList->pHead->data.studentID.c_str(), pCur->data.studentID.c_str()) > 0) {
				else if (compareIDStudent(stuList->pHead->data.studentID, pCur->data.studentID) == 1) { // CurID < head.StuID
					stuList->pHead->pPreStu = pCur;
					pCur->pNextStu = stuList->pHead;
					stuList->pHead = pCur;
				}

				else {
					_Student* pRun = stuList->pHead;
					//	while (strcmp(pRun->data.studentID.c_str(), pCur->data.studentID.c_str()) < 0) pRun = pRun->pNextStu;
					while (compareIDStudent(pRun->data.studentID, pCur->data.studentID) == 2) pRun = pRun->pNextStu; // check until run > cur (while cur > run)
					pCur->pNextStu = pRun;
					pCur->pPreStu = pRun->pPreStu;
					pRun->pPreStu->pNextStu = pCur;
					pRun->pPreStu = pCur;
				}
			}

			getline(fileIn, pCur->data.lastName, ',');
			getline(fileIn, pCur->data.firstName, ',');

			for (int i = 0; i < 3; i++) getline(fileIn, temp, ',');
		}
		else { //add grade to existed node
			for (int i = 0; i < 5; i++) getline(fileIn, temp, ',');
		}
		getline(fileIn, temp, ',');
		//std::cout << "CourseID = " << temp << std::endl;
		int check = isFoundation(temp);

		for (int i = 0; i < 2; i++) getline(fileIn, temp, ',');

		getline(fileIn, temp, ',');
		float gpa;
		if (temp == "NULL") gpa = 0;
		else gpa = stof(temp);
		getline(fileIn, temp, ',');
		getline(fileIn, temp);
		int credit = stoi(temp);

		if (gpa >= 5) pCur->data.gpa.credit_Accumulated += credit; //check the score if the student is failed or not to add in the credits of that course
		if (check == 0) {
			pCur->data.gpa.GPA_All += gpa * credit;
			pCur->data.gpa.GPA_Foundation += gpa * credit;
			pCur->data.gpa.credits_Foundation += credit;
		}
		if (check == 1) {
			pCur->data.gpa.credits_Sub += credit;
		}
		if (check == 2) {
			pCur->data.gpa.GPA_All += gpa * credit;
			pCur->data.gpa.credits_General += credit;
		}
	}
	return stuList;
}

_Major* createMajorList(std::string fileName) { //read file Major and create a Major linked list
	std::ifstream f;
	f.open(fileName, std::ios::in);
	if (!f.is_open()) return nullptr;

	_Major* list = nullptr;
	_Major* pCur = list;
	std::string line;
	getline(f, line);
	while (!f.eof()) {
		getline(f, line, ',');
		if (line == "") break;

		getline(f, line, ',');
		if (list == nullptr) {
			list = new _Major;
			pCur = list;
		}
		else {
			pCur->pNextMajor = new _Major;
			pCur->pNextMajor->pPreMajor = pCur;
			pCur = pCur->pNextMajor;
		}
		pCur->data.shortName = line;
		getline(f, line);
		pCur->data.quota = stoi(line);
	}
	return list;
}

void add_Interests(std::string fileName, StudentList* studList) { //read file Interests and add Interest of student into the existed students linked list
	std::ifstream f;
	f.open(fileName, std::ios::in);

	if (!f.is_open()) {
		std::cout << "Cant read file" << std::endl;
		return;
	}

	std::string line;
	getline(f, line);
	int i = 1;
	while (!f.eof()) {
		getline(f, line, ',');
		if (line == "") return;
		_Student* pCur = findStu(studList->pHead, studList->pTail, line); //find the Student with the same ID
		std::string tmp = line;

		if (pCur == nullptr) getline(f, line); //if the student is not existed in Grading file
		else { //take the Interests information of that student
			std::string name1;
			std::string name2;
			getline(f, name1, ',');
			getline(f, name2, ',');
			if (pCur->pNextStu != nullptr && pCur->pNextStu->data.studentID == pCur->data.studentID && pCur->pNextStu->data.lastName == name1 && pCur->pNextStu->data.firstName == name2) pCur = pCur->pNextStu;
			else if (pCur->pPreStu != nullptr && pCur->pPreStu->data.studentID == pCur->data.studentID && pCur->pPreStu->data.lastName == name1 && pCur->pPreStu->data.firstName == name2) pCur = pCur->pPreStu;

			getline(f, line, ',');
			for (int i = 0; i < 5; i++) getline(f, pCur->data.interest.desiredMajor[i], ',');
			getline(f, pCur->data.interest.desiredMajor[5]);
			i++;
		}
	}
}

void insertIntoSortedList(StudentList& list, _Student* node) { //Insert a student into a Major
	node->pNextStu = nullptr;
	node->pPreStu = nullptr;
	if (list.pHead == nullptr) { //if the student is considered the first one in the list
		list.pHead = node;
		list.pTail = node;
	}
	//compare to insert the student for the list to go in order
	else { //if gpa of cur is bigger than head
		if (node->data.gpa > list.pHead->data.gpa) {
			node->pNextStu = list.pHead;
			list.pHead->pPreStu = node;
			list.pHead = node;
		}

		else if (list.pTail->data.gpa > node->data.gpa) { //if gpa of cur is lower than tail
			node->pPreStu = list.pTail;
			list.pTail->pNextStu = node;
			list.pTail = node;
		}

		else { 
			_Student* cur = list.pTail;
			while (cur != list.pHead && !(cur->data.gpa > node->data.gpa)) cur = cur->pPreStu;
			node->pNextStu = cur->pNextStu;
			cur->pNextStu->pPreStu = node;
			node->pPreStu = cur;
			cur->pNextStu = node;
		}
	}
}

void insertStuIntoMajors(_Major* majorList, StudentList* stuList) {//Insert every students into 6 majors
	_Student* pCur = stuList->pHead;
	while (pCur != nullptr) {

		if (pCur->data.interest.desiredMajor[0] == "" || pCur->data.interest.chosen > 5) pCur = pCur->pNextStu;

		else {
			_Major* pMajor = majorList;

			while (pMajor->data.shortName != pCur->data.interest.desiredMajor[pCur->data.interest.chosen]) pMajor = pMajor->pNextMajor;
			if (pMajor->data.quota > 0) { // case remaining
				_Student* pTmp = pCur;

				if (pCur == stuList->pHead) {
					stuList->pHead = pCur->pNextStu;
					stuList->pHead->pPreStu = nullptr;
				}

				else if (pCur == stuList->pTail) {
					stuList->pTail = stuList->pTail->pPreStu;
					stuList->pTail->pNextStu = nullptr;
				}

				else {
					pCur->pPreStu->pNextStu = pCur->pNextStu;
					pCur->pNextStu->pPreStu = pCur->pPreStu;
				}

				pCur = pCur->pNextStu;
				insertIntoSortedList(pMajor->data.stuList, pTmp);
				pMajor->data.quota--;

			}

			else { // case: full slot
				if (pMajor->data.stuList.pTail->data.gpa > pCur->data.gpa) { // case: pCur < Tail => out
					if (pCur->data.interest.chosen == 5) pCur = pCur->pNextStu;
					else pCur->data.interest.chosen++;
				}
				else {
					_Student* tmp = pCur;
					_Student* tail = pMajor->data.stuList.pTail;

					if (pCur == stuList->pHead) stuList->pHead = tail;
					else pCur->pPreStu->pNextStu = tail;

					tail->pNextStu = pCur->pNextStu;

					if (pCur == stuList->pTail) stuList->pTail = tail;
					else pCur->pNextStu->pPreStu = tail;

					pCur = tail;
					pMajor->data.stuList.pTail = pMajor->data.stuList.pTail->pPreStu;
					pMajor->data.stuList.pTail->pNextStu = nullptr;
					pCur->pPreStu = tmp->pPreStu;
					insertIntoSortedList(pMajor->data.stuList, tmp);
					++pCur->data.interest.chosen;

				}
			}

		}
	}
}

void deallocatedStudentList(_Student*& stuList) { //deallocate student linked list
	_Student* pCur = stuList;
	while (stuList != nullptr) {
		stuList = stuList->pNextStu;
		delete pCur;
		pCur = stuList;
	}
}

void deallocatedMajorList(_Major*& majorList) {//deallocate major linked list
	_Major* pCur = majorList;
	while (majorList != nullptr) {
		majorList = majorList->pNextMajor;
		deallocatedStudentList(pCur->data.stuList.pHead);
		delete pCur;
		pCur = majorList;
	}
}

int main(int argc, char* argv[]) {
	StudentList* list = readGrading("Grading.csv");
	//std::cout << "Success!" << std::endl;
	add_Interests("Interests.csv", list);
	_Major* majorList = createMajorList("Majors.csv");
	//std::cout << "Success!" << std::endl;

	insertStuIntoMajors(majorList, list);

	//std::cout << "Success!" << std::endl;
	//_Major* pCurMajor = majorList;
	//while (pCurMajor != nullptr) {
	//	
	//	std::cout << "Shorted name: " << pCurMajor->data.shortName << std::endl;
	//	_Student* cur = pCurMajor->data.stuList.pHead;
	//	int i = 0;
	//	std::cout << "Remaining: " << pCurMajor->data.quota << std::endl;
	//	while (cur != nullptr) {
	//		std::cout << "MSSV: " << cur->data.studentID << " - GPA Foundation: " << cur->data.gpa.GPA_Foundation << std::endl;
	//		cur = cur->pNextStu;
	//		i++;
	//	}
	//	std::cout << "number of students: " << i << std::endl;
	//	std::cout << std::endl;
	//	pCurMajor = pCurMajor->pNextMajor;
	//}

	//std::cout << "Others student: " << std::endl;
	//_Student* pCurStu = list->pHead;
	//while (pCurStu != nullptr) {
	//	std::cout << "MSSV: " << pCurStu->data.studentID << " " << pCurStu->data.gpa.GPA_Foundation << std::endl;
	//	pCurStu = pCurStu->pNextStu;
	//}


	if (strcmp(argv[1], "-all")==0)
	{
		fullMajorResult(majorList,list);
	}
	else if (strcmp(argv[1], "-s")==0)
	{
		resultOfOneStu(argv[2], majorList,list);
	}
	else if (strcmp(argv[1], "-m")==0)
	{
		resultOfOneM(argv[2], majorList);
	}
	else
	{
		std::cout << "Invalid choice";
	}


	deallocatedStudentList(list->pHead);
	deallocatedMajorList(majorList);
	return 0;
}