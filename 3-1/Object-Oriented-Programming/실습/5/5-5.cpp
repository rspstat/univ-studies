#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
using namespace std;

struct Subject {           // 과목 정보
    char SubName[30];      // 과목 이름
    int Hakjum;            // 과목 학점
    char Grade[10];        // 과목 등급
    float GPA;             // 과목 평점
};

struct Student {           // 학생 정보
    char StdName[30];      // 학생 이름
    int Hakbun;            // 학번
    Subject* Sub;          // 과목
    int SubNum;            // 과목 수
    float AveGPA;          // 평균 평점
};

// 함수 프로토타입 선언
inline void PrintMenu();                           // 메뉴 출력
inline void InputValue(char* str);                 // 문자열 입력
inline void InputValue(int& i);                    // 정수 입력

void InputScores();                                // 학생 성적 입력
void InputData(Student* pSt, int StudentNum);      // 전체 학생 입력
void ShowAllScores();                              // 전체 성적 출력
void PrintOneData(const Student& rSt);             // 한 학생 정보 출력
void PrintAllStdList(const Student* pSt, int StudentNum);  // 전체 학생 목록 출력
void ModifyStdInfo(Student* pSt, int StdNum);      // 학생 정보 수정
Student* StdSearch(Student* pSt, int StudentNum, const char* name);  // 학생 검색
void CalcGPA(Subject& Sub);                        // 등급 -> 평점 변환
float CalcAveGPA(Subject* Sub, int SubNum);        // GPA 평균 계산

Student* student = nullptr;    // 동적 할당된 학생 배열 포인터
int StdNum = 0;                // 전체 학생 수

int main() {
    while (true) {
        PrintMenu();       // 메뉴 출력
        int choice;
        cin >> choice;     // 메뉴 선택
        cout << "\n";

        switch (choice) {
        case 1:    // 성적 입력
            InputScores(); 
            break;
        case 2:     // 전체 성적 입력
            ShowAllScores(); 
            break;
        case 3: {   // 학생 검색
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
        case 4:     // 학생 목록 출력
            PrintAllStdList(student, StdNum); 
            break;
        case 5:     // 정보 수정
            ModifyStdInfo(student, StdNum);   
            break;
        case 6:     // 프로그램 종료
            cout << "프로그램을 종료합니다.\n";
            for (int i = 0; i < StdNum; ++i) {
                delete[] student[i].Sub;      // 과목 메모리 해제
            }
            delete[] student;                 // 학생 메모리 해제
            return 0;

        default:    // 예외 처리
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

inline void InputValue(char* str) {
    cin >> str;
}

inline void InputValue(int& i) {
    cin >> i;
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
    InputData(student, StdNum);          // 학생 정보 입력
}

void InputData(Student* pSt, int StudentNum) {
    for (int i = 0; i < StudentNum; ++i) {
        cout << "\n* " << i + 1 << " 번째 학생 이름과 학번을 입력하세요.\n";
        cout << "이름 : ";
        InputValue(pSt[i].StdName);
        cout << "학번 : ";
        InputValue(pSt[i].Hakbun);
        cout << "\n수강한 과목 수를 입력하세요 : ";
        InputValue(pSt[i].SubNum);             // 과목 수 입력

        pSt[i].Sub = new Subject[pSt[i].SubNum];  // 과목 배열 동적 할당
        pSt[i].AveGPA = 0;

        for (int j = 0; j < pSt[i].SubNum; ++j) {
            cout << "교과목명 : ";
            InputValue(pSt[i].Sub[j].SubName);
            cout << "과목학점수 : ";
            InputValue(pSt[i].Sub[j].Hakjum);
            cout << "과목등급<A+ ~ F> : ";
            cin >> pSt[i].Sub[j].Grade;
            cout << "\n";

            CalcGPA(pSt[i].Sub[j]);              // 평점 계산
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
        if (strcmp(pSt[i].StdName, name) == 0) {
            return &pSt[i];        // 이름 일치하면 반환
        }
    }

    return nullptr;               // 없으면 nullptr
}

void PrintOneData(const Student& rSt) {
    if (rSt.StdName == nullptr) return;
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

void CalcGPA(Subject& Sub) {
    if (strcmp(Sub.Grade, "A+") == 0) Sub.GPA = 4.5f;
    else if (strcmp(Sub.Grade, "A0") == 0 || strcmp(Sub.Grade, "A") == 0) Sub.GPA = 4.0f;
    else if (strcmp(Sub.Grade, "B+") == 0) Sub.GPA = 3.5f;
    else if (strcmp(Sub.Grade, "B0") == 0 || strcmp(Sub.Grade, "B") == 0) Sub.GPA = 3.0f;
    else if (strcmp(Sub.Grade, "C+") == 0) Sub.GPA = 2.5f;
    else if (strcmp(Sub.Grade, "C0") == 0 || strcmp(Sub.Grade, "C") == 0) Sub.GPA = 2.0f;
    else if (strcmp(Sub.Grade, "D+") == 0) Sub.GPA = 1.5f;
    else if (strcmp(Sub.Grade, "D0") == 0 || strcmp(Sub.Grade, "D") == 0) Sub.GPA = 1.0f;
    else Sub.GPA = 0.0f;
}

float CalcAveGPA(Subject* Sub, int SubNum) {
    float StudentNumGPA = 0;
    for (int i = 0; i < SubNum; i++) {
        StudentNumGPA += Sub[i].GPA;
    }
    return StudentNumGPA / SubNum;
}
