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

        switch (choice) {
        case 1: // 성적 입력
            cout << "\n";
            InputScores();
            break;
        case 2: // 전체 성적 보기
            cout << "\n";
            ShowAllScores();
            break;
        case 3: { // 학생 검색
            char name[30];
            cout << "\n검색할 학생의 이름 : ";
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
            cout << "\n";
            ModifyStdInfo(student, StdNum);
            break;
        case 6: // 프로그램 종료
            cout << "\n프로그램을 종료합니다.\n";
            delete[] student;
            return 0;
        case 7: // 전체 학생 수 확인
            cout << "현재 등록된 학생 수 : "
                << Student::GetStudentCount() << "명\n";
            break;
        default: // 예외처리
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
        << "7. 전체 학생 수 확인\n"
        << "\n선택 : ";
}

void InputScores() {
    cout << "전체 학생 수 입력 : ";
    cin >> StdNum;

    if (student != nullptr) {
        for (int i = 0; i < StdNum; ++i) {
            delete[] student[i].GetSubjects();
        }
        delete[] student;
    }

    student = new Student[StdNum];
    InputData(student, StdNum);
}

void InputData(Student* pSt, int StudentNum) {
    for (int i = 0; i < StudentNum; ++i) {
        cout << "\n* " << i + 1 << " 번째 학생 이름과 학번을 입력하세요.\n";
        cout << "이름 : ";
        string name; pSt[i].InputValue(name); pSt[i].SetStdName(name);
        cout << "학번 : ";
        int hakbun; pSt[i].InputValue(hakbun); pSt[i].SetHakbun(hakbun);
        cout << "\n수강한 과목 수를 입력하세요 : ";
        int subNum; pSt[i].InputValue(subNum); pSt[i].SetSubNum(subNum);

        pSt[i].SetSub(new Subject[pSt[i].GetSubNum()]); // 과목 배열 동적 할당
        pSt[i].SetAveGPA(0.0f);

        for (int j = 0; j < pSt[i].GetSubNum(); ++j) {
            Subject* subs = pSt[i].GetSubjects();
            subs[j].InputData();                 // 과목 입력
            pSt[i].CalcGPA(subs[j]);             // 평점 계산
            pSt[i].SetAveGPA(pSt[i].GetAveGPA() + subs[j].GetGPA());
        }

        pSt[i].SetAveGPA(pSt[i].GetAveGPA() / pSt[i].GetSubNum()); // 평균 평점 계산
    }
}

void ShowAllScores() {
    cout << "   전체 학생 성적 보기\n";
    for (int i = 0; i < StdNum; i++) {
        cout << "====================================================\n";
        cout << "학번 : " << student[i].GetHakbun()
            << " 이름 : " << student[i].GetStdName() << "\n";
        cout << "====================================================\n";
        cout << "과목명" << setw(10) << "과목학점" << setw(10) << "과목등급" << setw(10) << "과목평점" << "\n";
        cout << "====================================================\n";

        for (int j = 0; j < student[i].GetSubNum(); j++) {
            Subject* subs = student[i].GetSubjects();
            cout << subs[j].GetSubName()
                << setw(10) << subs[j].GetHakjum()
                << setw(10) << subs[j].GetGrade()
                << setw(10) << fixed << setprecision(2)
                << subs[j].GetGPA() * subs[j].GetHakjum() << "\n";
        }
        cout << "====================================================\n";
        cout << setw(20) << "평균평점 : "
            << setw(10) << fixed << setprecision(2)
            << student[i].GetAveGPA() << "\n\n";
    }
}

Student* StdSearch(Student* pSt, int StudentNum, const char* name) {
    for (int i = 0; i < StudentNum; ++i) {
        if (pSt[i].GetStdName() == name) {
            return &pSt[i];
        }
    }
    return nullptr;
}

void PrintOneData(const Student& rSt) {
    cout << "이름: " << rSt.GetStdName()
        << " 학번: " << rSt.GetHakbun() << "\n";
    cout << "====================================================\n";
    cout << setw(20) << "과목명" << setw(10) << "학점" << setw(10) << "등급" << setw(10) << "평점" << "\n";
    cout << "====================================================\n";
    for (int j = 0; j < rSt.GetSubNum(); j++) {
        Subject* subs = rSt.GetSubjects();
        cout << setw(10) << subs[j].GetSubName()
            << setw(10) << subs[j].GetHakjum()
            << setw(10) << subs[j].GetGrade()
            << setw(10) << fixed << setprecision(2)
            << subs[j].GetGPA() * subs[j].GetHakjum() << "\n";
    }
    cout << "====================================================\n";
    cout << setw(20) << "평균평점 : " << fixed << setprecision(2) << rSt.GetAveGPA() << "\n";
}

void PrintAllStdList(const Student* pSt, int StudentNum) {
    cout << "\n==================================\n";
    cout << setw(10) << "학번" << setw(10) << " 이름\n";
    cout << "==================================\n";
    for (int i = 0; i < StudentNum; i++) {
        cout << setw(10) << pSt[i].GetHakbun()
            << setw(10) << pSt[i].GetStdName() << "\n";
    }
    cout << "==================================\n";
    cout << "\n";
}

void ModifyStdInfo(Student* pSt, int StdNum) {
    string name;
    cout << "검색 할 학생 이름 : ";
    cin >> name;
    Student* SearchName = StdSearch(pSt, StdNum, name.c_str());
    if (SearchName == nullptr) {
        cout << "해당 학생을 찾을 수 없습니다.\n";
        return;
    }

    cout << "* <" << SearchName->GetStdName() << ", " << SearchName->GetHakbun() << "> 의 정보를 수정하세요\n";
    cout << "이름 : ";
    string newName; cin >> newName; SearchName->SetStdName(newName);
    cout << "학번 : ";
    int newHakbun; cin >> newHakbun; SearchName->SetHakbun(newHakbun);
}

