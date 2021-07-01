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
	getline(fileIn, temp); // skip 1 row
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
				pCur->data.gpa.GPA_All /= (pCur->data.gpa.credits_General + pCur->data.gpa.credits_Foundation);
				pCur->data.gpa.GPA_Foundation /= pCur->data.gpa.credits_Foundation;
				pCur = new _Student;
				pCur->pNextStu = nullptr;
				pCur->pPreStu = nullptr;
				pCur->data.studentID = temp;
				//std::cout << "MSSV = " << pCur->data.studentID << std::endl;

				if (compareIDStudent(stuList->pTail->data.studentID, pCur->data.studentID) == 2) {// CurID >  tail.StudentID 
					stuList->pTail->pNextStu = pCur;
					pCur->pPreStu = stuList->pTail;
					stuList->pTail = pCur;
				}

				else if (compareIDStudent(stuList->pHead->data.studentID, pCur->data.studentID) == 1) { // CurID < head.StuID
					stuList->pHead->pPreStu = pCur;
					pCur->pNextStu = stuList->pHead;
					stuList->pHead = pCur;
				}
				
				else {
					_Student* pRun = stuList->pHead;
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

int main() {
	StudentList* list = readGrading("Grading.csv");
	
	while (list->pHead != nullptr) {
		std::cout << "MSSV: " << list->pHead->data.studentID << " with GPA Foundation = " << list->pHead->data.gpa.GPA_Foundation << std::endl;
		list->pHead = list->pHead->pNextStu;
	}

	return 0;
}