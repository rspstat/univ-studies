// Subject.h
#ifndef SUBJECT_H
#define SUBJECT_H

#include <iostream>
#include <string>
using namespace std;

class Subject {
private:
    string SubName;   // 과목명
    int Hakjum;    // 학점
    string Grade;     // 등급
    float GPA;       // 평점

public:
    Subject();             // 생성자
    ~Subject();            // 소멸자

    void InputData();    // 데이터 입력
    void CalcGPA();      // 평점 계산
    void PrintData() const; // 정보 출력
    float GetGPA() const; // GPA 반환

    // 접근자
    string GetSubName() const;  // 과목명 반환
    int GetHakjum() const;  // 학점 반환
    string GetGrade() const;  // 등급 반환

    // 수정자
    void SetSubName(const string&); // 과목명 설정
    void SetHakjum(int);            // 학점 설정
    void SetGrade(const string&);   // 등급 설정
};

#endif
