// Student.cpp
#include "Student.h"
#include <iostream>
using namespace std;

int Student::studentCount = 0;

Student::Student() {
    StdName = "";
    Hakbun = 0;
    SubNum = 0;
    Sub = nullptr;
    AveGPA = 0.0f;
    studentCount++;
}

Student::~Student() {
    delete[] Sub;
    studentCount--;
}

void Student::CalcGPA(Subject& sub) {
    sub.CalcGPA();
}

float Student::CalcAveGPA(Subject* subArr, int SubNum) {
    float sum = 0.0f;
    for (int i = 0; i < SubNum; ++i)
        sum += subArr[i].GetGPA();
    return (SubNum > 0) ? sum / SubNum : 0.0f;
}

// 접근자 구현
string Student::GetStdName() const { return StdName; }
int Student::GetHakbun() const { return Hakbun; }
int Student::GetSubNum() const { return SubNum; }
Subject* Student::GetSubjects() const { return Sub; }
float Student::GetAveGPA() const { return AveGPA; }
int Student::GetStudentCount() { return studentCount; }

// 수정자 구현
void Student::SetStdName(const string& name) { StdName = name; }
void Student::SetHakbun(int num) { Hakbun = num; }
void Student::SetSubNum(int num) { SubNum = num; }
void Student::SetSub(Subject* ptr) { Sub = ptr; }
void Student::SetAveGPA(float avg) { AveGPA = avg; }
