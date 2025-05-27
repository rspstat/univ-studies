// main.cpp
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Subject.h"
#include "Student.h"

using namespace std;

// 함수 프로토타입
inline void PrintMenu();    
void InputScores();
void InputData(Student* pSt, int StudentNum);
void ShowAllScores();
Student* StdSearch(Student* pSt, int StudentNum, const char* name);
void PrintOneData(const Student& rSt);
void PrintAllStdList(const Student* pSt, int StudentNum);
void ModifyStdInfo(Student* pSt, int StdNum);

// 전역 변수
Student* student = nullptr;
int StdNum = 0;

int main() {
    while (true) {
        PrintMenu();
        int choice;
        cin >> choice;
        cout << "\n";

        switch (choice) {
        case 1: // 성적 입력
            InputScores();
            break;
        case 2: // 전체 성적 보기
            ShowAllScores();
            break;
        case 3: { // 학생 검색
            char name[30];
            cout << "검색할 학생의 이름 : ";
            cin >> name;
            Student* found = StdSearch(student, StdNum, name);
            if (found == nullptr) {
                cout << "해당 이름의 학생을 찾을 수 없습니다.\n";
            }
            else {
                PrintOneData(*found);
            }
            break;
        }
        case 4: // 학생 목록 출력
            PrintAllStdList(student, StdNum);
            break;
        case 5: // 정보 수정
            ModifyStdInfo(student, StdNum);
            break;
        case 6: // 프로그램 종료
            cout << "프로그램을 종료합니다.\n";
            delete[] student;
            return 0;
        default:
            cout << "잘못된 입력입니다. 다시 선택해주세요.\n";
            break;
        }
        cout << "\n";
    }
    return 0;
}

inline void PrintMenu() {
    cout << "===== 메뉴 =====\n"
        << "1. 학생 성적 입력\n"
        << "2. 전체 학생 성적 보기\n"
        << "3. 학생 이름 검색\n"
        << "4. 전체 학생 목록 보기\n"
        << "5. 학생 정보 수정\n"
        << "6. 프로그램 종료\n"
        << "\n원하는 기능을 입력하세요 : ";
}

void InputScores() {
    cout << "전체 학생 수 입력 : ";
    cin >> StdNum;

    if (student != nullptr) {
        for (int i = 0; i < StdNum; ++i) {
            delete[] student[i].Sub;      // 기존 과목 메모리 해제
        }
        delete[] student;                 // 기존 학생 메모리 해제
    }

    student = new Student[StdNum];        // 학생 동적 할당
    InputData(student, StdNum);
}

void InputData(Student* pSt, int StudentNum) {
    for (int i = 0; i < StudentNum; ++i) {
        cout << "\n* " << i + 1 << " 번째 학생 이름과 학번을 입력하세요.\n";
        cout << "이름 : ";
        pSt[i].InputValue(pSt[i].StdName);
        cout << "학번 : ";
        pSt[i].InputValue(pSt[i].Hakbun);
        cout << "\n수강한 과목 수를 입력하세요 : ";
        pSt[i].InputValue(pSt[i].SubNum);             // 과목 수 입력

        pSt[i].Sub = new Subject[pSt[i].SubNum];  // 과목 배열 동적 할당
        pSt[i].AveGPA = 0;

        for (int j = 0; j < pSt[i].SubNum; ++j) {
            cout << "교과목명 : ";
            pSt[i].InputValue(pSt[i].Sub[j].SubName);
            cout << "과목학점수 : ";
            pSt[i].InputValue(pSt[i].Sub[j].Hakjum);
            cout << "과목등급<A+ ~ F> : ";
            cin >> pSt[i].Sub[j].Grade;
            cout << "\n";

            pSt[i].CalcGPA(pSt[i].Sub[j]);              // 평점 계산
            pSt[i].AveGPA += pSt[i].Sub[j].GPA;
        }

        pSt[i].AveGPA /= pSt[i].SubNum;          // 평균 평점 계산
        cout << "\n";
    }
}

void ShowAllScores() {
    cout << "   전체 학생 성적 보기\n";
    for (int i = 0; i < StdNum; i++) {
        cout << "====================================================\n";
        cout << "학번 : " << student[i].Hakbun << " 이름 : " << student[i].StdName << "\n";
        cout << "====================================================\n";
        cout << "과목명" << setw(10) << "과목학점" << setw(10) << "과목등급" << setw(10) << "과목평점" << "\n";
        cout << "====================================================\n";

        for (int j = 0; j < student[i].SubNum; j++) {
            cout << student[i].Sub[j].SubName
                << setw(10) << student[i].Sub[j].Hakjum
                << setw(10) << student[i].Sub[j].Grade
                << setw(10) << fixed << setprecision(2)
                << student[i].Sub[j].GPA * student[i].Sub[j].Hakjum << "\n";
        }
        cout << "====================================================\n";
        cout << setw(20) << "평균평점 : " << setw(10) << fixed << setprecision(2) << student[i].AveGPA << "\n\n";
    }
}

Student* StdSearch(Student* pSt, int StudentNum, const char* name) {
    for (int i = 0; i < StudentNum; ++i) {
        if (pSt[i].StdName == name) {
            return &pSt[i];        // 이름 일치하면 반환
        }
    }

    return nullptr;               // 없으면 nullptr
}

void PrintOneData(const Student& rSt) {
    cout << "이름: " << rSt.StdName << " 학번: " << rSt.Hakbun << "\n";
    cout << "====================================================\n";
    cout << setw(20) << "과목명" << setw(10) << "학점" << setw(10) << "등급" << setw(10) << "평점" << "\n";
    cout << "====================================================\n";
    for (int j = 0; j < rSt.SubNum; j++) {
        cout << setw(10) << rSt.Sub[j].SubName
            << setw(10) << rSt.Sub[j].Hakjum
            << setw(10) << rSt.Sub[j].Grade
            << setw(10) << fixed << setprecision(2)
            << rSt.Sub[j].GPA * rSt.Sub[j].Hakjum << "\n";
    }
    cout << "====================================================\n";
    cout << setw(20) << "평균평점 : " << fixed << setprecision(2) << rSt.AveGPA << "\n";
}

void PrintAllStdList(const Student* pSt, int StudentNum) {
    cout << "\n==================================\n";
    cout << setw(10) << "학번" << setw(10) << " 이름\n";
    cout << "==================================\n";
    for (int i = 0; i < StudentNum; i++) {
        cout << setw(10) << pSt[i].Hakbun
            << setw(10) << pSt[i].StdName << "\n";
    }
    cout << "==================================\n";
    cout << "\n";
}

void ModifyStdInfo(Student* pSt, int StdNum) {
    string name;
    cout << "검색 할 학생 이름 : ";
    cin >> name;
    Student* target = StdSearch(pSt, StdNum, name.c_str());
    if (target == nullptr) {
        cout << "해당 학생을 찾을 수 없습니다.\n";
        return;
    }
    cout << "* <" << target->StdName << ", " << target->Hakbun << "> 의 정보를 수정하세요\n";
    cout << "이름 : ";
    cin >> target->StdName;
    cout << "학번 : ";
    cin >> target->Hakbun;
}