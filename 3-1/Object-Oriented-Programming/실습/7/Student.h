// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "Subject.h"
using namespace std;

class Student {
private:
    string StdName;    // 이름
    int Hakbun;     // 학번
    int SubNum;     // 과목 수
    Subject* Sub;        // 과목 배열
    float AveGPA;     // 평균 평점

    static int studentCount;  // 학생 수 카운팅

public:
    Student();             // 생성자
    ~Student();            // 소멸자

    // 저번 6주차 때 InputData는 빼기로 하였습니다.

    void CalcGPA(Subject& sub);                 // 평점 계산 호출
    float CalcAveGPA(Subject* sub, int SubNum);  // 평균 계산

    inline void InputValue(int& i) { cin >> i; }
    inline void InputValue(string& s) { cin >> s; }

    // 접근자
    string GetStdName() const;  // 이름 반환
    int GetHakbun() const;  // 학번 반환
    int GetSubNum() const;  // 과목 수 반환
    Subject* GetSubjects() const;  // 과목 배열 반환
    float GetAveGPA() const;  // 평균 평점 반환

    static int GetStudentCount();  // 학생 수 반환

    // 수정자
    void SetStdName(const string&); // 이름 설정
    void SetHakbun(int);            // 학번 설정
    void SetSubNum(int);            // 과목 수 설정
    void SetSub(Subject*);          // 과목 배열 설정
    void SetAveGPA(float);          // 평균 평점 설정
};

#endif
