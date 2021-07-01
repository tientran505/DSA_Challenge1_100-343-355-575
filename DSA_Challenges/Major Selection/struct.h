#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <codecvt>
#include <locale>

//student
struct Date {
	int day, month, year;
};

struct MajorStu {
	std::string desiredMajor[6];
	int chosen = 0;
};

struct GPA {
	float GPA_Foundation = 0;
	float GPA_All = 0;
	int credits_Foundation = 0;
	int credits_General = 0;
	int credits_Sub = 0;
	int credit_Accumulated = 0;
};

struct Student {
	std::string studentID;
	std::string lastName;
	std::string firstName;
	Date regDate;
	GPA gpa;
	MajorStu interest;
};

struct _Student {
	Student data;
	_Student* pNextStu = nullptr;
	_Student* pPreStu = nullptr;
};

struct StudentList {
	_Student* pHead = nullptr;
	_Student* pTail = nullptr;
};
//major

struct Major {
	std::wstring name;
	std::string shortName;
	int quota;

	StudentList stuList;
};

struct _Major {
	Major data;
	_Major* pNextMajor = nullptr;
	_Major* pPreMajor = nullptr;
};

#endif _STRUCT_H_
