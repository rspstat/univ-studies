// Student.cpp
#include "Student.h"
#include <iostream>
using namespace std;

Student::Student() {
    StdName = "";
    Hakbun = 0;
    SubNum = 0;
    Sub = nullptr;
    AveGPA = 0.0f;
}

Student::~Student() {
    delete[] Sub;
}

void Student::CalcGPA(Subject& sub) {
    sub.CalcGPA();
}

float Student::CalcAveGPA(Subject* sub, int SubNum) {
    float sum = 0.0f;
    for (int i = 0; i < SubNum; i++) {
        sum += sub[i].GetGPA();
    }
    return (SubNum > 0) ? sum / SubNum : 0.0f;
}