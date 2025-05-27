// Subject.cpp
#include "Subject.h"
#include <iostream>
using namespace std;

Subject::Subject() {
    SubName = "";
    Hakjum = 0;
    Grade = "F";
    GPA = 0.0f;
}

Subject::~Subject() {}

void Subject::InputData() {
    cout << "교과목명 : ";
    cin >> SubName;
    cout << "과목학점수 : ";
    cin >> Hakjum;
    cout << "과목등급<A+ ~ F> : ";
    cin >> Grade;
    cout << "\n";
}

void Subject::CalcGPA() {
    if (Grade == "A+") GPA = 4.5f;
    else if (Grade == "A0" || Grade == "A") GPA = 4.0f;
    else if (Grade == "B+") GPA = 3.5f;
    else if (Grade == "B0" || Grade == "B") GPA = 3.0f;
    else if (Grade == "C+") GPA = 2.5f;
    else if (Grade == "C0" || Grade == "C") GPA = 2.0f;
    else if (Grade == "D+") GPA = 1.5f;
    else if (Grade == "D0" || Grade == "D") GPA = 1.0f;
    else GPA = 0.0f;
}

void Subject::PrintData() const {
    cout << "과목명: " << SubName
        << ", 학점: " << Hakjum
        << ", 등급: " << Grade
        << ", 평점: " << GPA << "\n";
}

float Subject::GetGPA() const {
    return GPA;
}