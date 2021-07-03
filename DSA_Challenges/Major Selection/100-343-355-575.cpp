#include "struct.h"

void wstringToString(std::wstring source, std::string& destination) {
	int length = source.size();
	for (int i = 0; i < length; i++) {
		destination[i] = source[i];
	}
}

int isFoundation(std::string str) { //0 foundation, 1 sub, 2 general
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

int compareIDStudent(std::string std1, std::string std2) { // return 1 if std1 > std2, 2 if std1 < std2, 0 if std1 == std2
	std::string tmp1 = std1;
	std::string tmp2 = std2;

	tmp1.erase(tmp1.begin(), tmp1.begin() + 2);
	tmp2.erase(tmp2.begin(), tmp2.begin() + 2);

	if (stoi(tmp1) < stoi(tmp2)) return 2;
	else if (stoi(tmp1) > stoi(tmp2)) return 1;
	else return 0;
}

_Student* nodeMiddle(_Student* head, _Student* tail) {
	if (head == nullptr) return nullptr;
	_Student* slow = head;
	_Student* fast = head->pNextStu;

	while (fast != tail) {
		fast = fast->pNextStu;
		if (fast != tail) {
			slow = slow->pNextStu;
			fast = fast->pNextStu;
		}
	}
	return slow;
}

bool checkDuplicate(_Student* head, _Student* tail,_Student* stu) {
	if (head == nullptr) return false;
	_Student* left = head;
	_Student* right = tail;
	while (compareIDStudent(left->data.studentID, right->data.studentID) == 2) { // while left < right
		_Student* mid = nodeMiddle(left, right);
		if (compareIDStudent(mid->data.studentID, stu->data.studentID) == 2) { // if mid < stu -> left = mid + 1;
			left = mid->pNextStu;
		}

		else if (compareIDStudent(mid->data.studentID, stu->data.studentID) == 1) { // if mid > stu -> right = mid - 1;
			right = mid->pPreStu;
		}
		else return true;
	}
	return false;
}

_Student* findStu(_Student* head, _Student* tail, std::string stuID) {
	if (head->data.studentID == stuID) return head;
	if (tail->data.studentID == stuID) return tail;
	_Student* left = head;
	_Student* right = tail;

	while (compareIDStudent(left->data.studentID, right->data.studentID) == 2) {
		_Student* mid = nodeMiddle(left, right);
		if (mid == nullptr) return nullptr;

		if (mid->data.studentID == stuID) return mid;

		else if (compareIDStudent(mid->data.studentID, stuID) == 2) left = mid->pNextStu;

		else right = mid->pPreStu;
	}
	return nullptr;
}

StudentList* readGrading(std::string fileName) {
	StudentList* stuList = nullptr;
	std::ifstream fileIn;
	fileIn.open(fileName, std::ios_base::in);

	if (!fileIn.is_open()) {
		std::cout << "Can't open\n";
		return nullptr;
	}

	stuList = new StudentList{ nullptr, nullptr };
	std::string temp;
	//getline(fileIn, temp); // skip 1 row
	_Student* pCur = nullptr;

	while (!fileIn.eof()) {
		getline(fileIn, temp, ','); //skip first col
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

		if (gpa >= 5) pCur->data.gpa.credit_Accumulated += credit;
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

_Major* creatMajorList(std::string fileName) {
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

void add_Interests(std::string fileName, StudentList* studList) {
	std::ifstream f;
	f.open(fileName, std::ios::in);

	if (!f.is_open()) {
		std::cout << "Cant read file" << std::endl;
		return;
	}

	std::string line;
	getline(f, line);
	while (!f.eof()) {
		getline(f, line, ',');
		if (line == "") return;
		_Student* pCur = findStu(studList->pHead, studList->pTail, line);

		if (pCur == nullptr) getline(f, line);

		else {
			getline(f, line, ',');
			if (pCur->pNextStu != nullptr && pCur->pNextStu->data.lastName == line) pCur = pCur->pNextStu;
			else if (pCur->pPreStu != nullptr && pCur->pPreStu->data.lastName == line) pCur = pCur->pPreStu;
			for (int i = 0; i < 2; i++) getline(f, line, ',');
			for (int i = 0; i < 5; i++) getline(f, pCur->data.interest.desiredMajor[i], ',');
			getline(f, pCur->data.interest.desiredMajor[5]);
		}
	}
}

int main() {
	StudentList* list = readGrading("Grading.csv");
	add_Interests("Interests.csv", list);

	_Major* majorList = creatMajorList("Majors.csv");
	
	while (list->pHead != nullptr) {
		std::cout << "MSSV: " << list->pHead->data.studentID << " with GPA Foundation = " << list->pHead->data.gpa.GPA_Foundation;
		std::cout << " | GPA All = " << list->pHead->data.gpa.GPA_All << std::endl;
		std::cout << "Interests: " << std::endl;
		for (int i = 0; i < 6; i++) {
			std::cout << i << ": " << list->pHead->data.interest.desiredMajor[i] << " | ";
		}
		std::cout << std::endl << std::endl;
		list->pHead = list->pHead->pNextStu;
	}
	while (majorList != nullptr) {
		std::cout << majorList->data.shortName << " - Quota: " << majorList->data.quota << std::endl;
		majorList = majorList->pNextMajor;
	}

	return 0;
}