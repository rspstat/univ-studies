// Subject.h
#ifndef SUBJECT_H
#define SUBJECT_H

#include <iostream>
#include <string>
using namespace std;

class Subject {
public:
    string SubName;  // 과목명
    int Hakjum;           // 학점
    string Grade;    // 등급
    float GPA;            // 평점

    Subject();            // 생성자
    ~Subject();           // 소멸자

    void InputData();     // 데이터 입력
    void CalcGPA();       // 평점 계산
    void PrintData() const; // 정보 출력
    float GetGPA() const; // GPA 반환
};

#endif