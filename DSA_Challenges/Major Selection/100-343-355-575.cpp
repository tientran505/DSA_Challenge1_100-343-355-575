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

void readGrading(std::string fileName, StudentList stuList) {
	std::ifstream fileIn;
	fileIn.open(fileName, std::ios_base::in);

	if (!fileIn.is_open()) {
		std::cout << "Can't open\n";
		return;
	}

	std::string temp;
	getline(fileIn, temp); // skip 1 row
	while (!fileIn.eof()) {
		getline(fileIn, temp, ','); //skip first col
		getline(fileIn, temp, ',');

		if (stuList.pTail == nullptr || stuList.pTail->data.studentID != temp) { //create new node
			if (stuList.pHead == nullptr) {
				stuList.pHead = new _Student;
				stuList.pTail = stuList.pHead;
			}
			else {
				stuList.pTail->data.gpa.GPA_All /= (stuList.pTail->data.gpa.credits_General + stuList.pTail->data.gpa.credits_Foundation);
				stuList.pTail->data.gpa.GPA_Foundation /= stuList.pTail->data.gpa.credits_Foundation;
				stuList.pTail->pNextStu = new _Student;
				stuList.pTail = stuList.pTail->pNextStu;
			}
			stuList.pTail->data.studentID = temp;
			getline(fileIn, stuList.pTail->data.lastName, ',');
			getline(fileIn, stuList.pTail->data.firstName, ',');
			
			for (int i = 0; i < 3; i++) getline(fileIn, temp, ',');
		}
		else { //add grade to existed node
			for (int i = 0; i < 5; i++) getline(fileIn, temp, ',');
		}

		getline(fileIn, temp, ',');
		int check = isFoundation(temp);

		for (int i = 0; i < 2; i++) getline(fileIn, temp, ',');

		getline(fileIn, temp, ',');
		float gpa = stof(temp);
		getline(fileIn, temp, ',');
		getline(fileIn, temp);
		int credit = stoi(temp);

		if (gpa >= 5) stuList.pTail->data.gpa.credit_Accumulated += credit;
		if (check == 0) {
			stuList.pTail->data.gpa.GPA_All += gpa * credit;
			stuList.pTail->data.gpa.GPA_Foundation += gpa * credit;
			stuList.pTail->data.gpa.credits_Foundation += credit;
		}
		if (check == 1) {
			stuList.pTail->data.gpa.GPA_All += gpa * credit;
			stuList.pTail->data.gpa.credits_General += credit;
		}
		if (check == 2) {
			stuList.pTail->data.gpa.credits_Sub += credit;
		}
	}
}

int main() {
	std::cout << "Test" << std::endl;
	return 0;
}