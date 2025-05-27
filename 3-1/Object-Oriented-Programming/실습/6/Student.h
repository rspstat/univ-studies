// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "Subject.h"
using namespace std;

class Student {
public:
    string StdName;       // 이름
    int Hakbun;           // 학번
    int SubNum;           // 과목 수
    Subject* Sub;         // 과목 배열
    float AveGPA;         // 평균 평점

    Student();            // 생성자
    ~Student();           // 소멸자

    void CalcGPA(Subject& sub);                   // 평점 계산 호출
    float CalcAveGPA(Subject* sub, int SubNum);   // 평균 계산

    inline void InputValue(int& i) {
        cin >> i;
    }

    inline void InputValue(string& str) {
        cin >> str;
    }
};

#endif