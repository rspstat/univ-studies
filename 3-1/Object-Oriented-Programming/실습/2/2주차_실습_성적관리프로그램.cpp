#include <iostream> // #include <bits/stdc++.h>
#include <iomanip>
#include <string>
#include <string.h>

using namespace std;

struct Subject {                     // 과목 정보
    char SubName[30]; // 과목이름
    int Hakjum;       // 과목학점
    char Grade[10];   // 과목등급
    float GPA;        // 과목 평점
};

struct Student {                     // 학생 정보
    char StdName[30]; // 학생  이름
    int Hakbun;       // 학번
    Subject Sub[3];   // 과목 (구조체 Subject)
    float AveGPA;     // 교과목 평균 평점
};

Student student[2]; 
Subject subject[3];

void main_menu();
void menu1();
void menu2();

int main() {

    while(1) {
        main_menu();    // 메인 메뉴 출력

        int temp = 0;
        cin >> temp;

        cout << "\n";

        // "\n" of time complexity is better than endl; -> 옛날에 백준 풀면서 알게된 사실
        if ( temp == 1 ) {
            menu1();
        }

        else if ( temp == 2 ) {
            menu2();			// 전체 학생의 신상/성적 정보 출력 
            system("pause");    // 출력되고 터미널이 자동 종료되는 것 방지
        }

        else 
            break;
    }
    
    return 0;
}

void menu1() {
    for (int i = 0; i < 2; i++) {
        cout << "\n* " << i + 1 << " 번째 학생 이름과 학번을 입력하세요." << "\n";	// 학생의 정보 입력 

        cout << "이름 : ";
        cin >> student[i].StdName;

        cout << "학번 : ";
        cin >> student[i].Hakbun;

        cout << "\n\n* 수강한 과목3개와 각 교과목명, 과목학점, 과목등급을 입력하세요." << "\n";

        student[i].AveGPA = 0;

        for (int j = 0; j < 3; j++) {
            cout << "교과목명 : ";
            cin >> student[i].Sub[j].SubName;
            cout << "과목학점수 : ";
            cin >> student[i].Sub[j].Hakjum;
            cout << "과목등급<A+ ~ F> : ";
            cin >> student[i].Sub[j].Grade;
            cout << "\n";

            if ( strcmp(student[i].Sub[j].Grade, "A+") == 0 ) // 교과목의 평점 계산 
                student[i].Sub[j].GPA = 4.5 * student[i].Sub[j].Hakjum;
            else if ( strcmp(student[i].Sub[j].Grade, "A0") == 0 || strcmp(student[i].Sub[j].Grade, "A") == 0 )
                student[i].Sub[j].GPA = 4.0 * student[i].Sub[j].Hakjum;
            else if ( strcmp(student[i].Sub[j].Grade, "B+") == 0 ) 
                student[i].Sub[j].GPA = 3.5 * student[i].Sub[j].Hakjum;
            else if ( strcmp(student[i].Sub[j].Grade, "B0") == 0 || strcmp(student[i].Sub[j].Grade, "B") == 0 )
                student[i].Sub[j].GPA = 3.0 * student[i].Sub[j].Hakjum;
            else if ( strcmp(student[i].Sub[j].Grade, "C+") == 0 ) 
                student[i].Sub[j].GPA = 2.5 * student[i].Sub[j].Hakjum;
            else if ( strcmp(student[i].Sub[j].Grade, "C0") == 0 || strcmp(student[i].Sub[j].Grade, "C") == 0 )
                student[i].Sub[j].GPA = 2.0 * student[i].Sub[j].Hakjum;
            else if ( strcmp(student[i].Sub[j].Grade, "D+") == 0 ) 
                student[i].Sub[j].GPA = 1.5 * student[i].Sub[j].Hakjum;
            else if ( strcmp(student[i].Sub[j].Grade, "D0") == 0 || strcmp(student[i].Sub[j].Grade, "D") == 0 )
                student[i].Sub[j].GPA = 1.0 * student[i].Sub[j].Hakjum;
            else
                student[i].Sub[j].GPA = 0.0;

            student[i].AveGPA += student[i].Sub[j].GPA;
        }
        
        student[i].AveGPA /= 3; // 개인 학생의 교과목 평균 평점 계산 
        
        cout << "\n";
    }
}

void menu2() {
    for (int i = 0; i < 2; i++) {
        cout << "   전체 학생 성적 보기" << "\n";
        cout << "====================================================" << "\n";
        cout << "이름 : " << student[i].StdName << " 학번 : " << student[i].Hakbun << "\n";
        cout << "====================================================" << "\n";
        cout << setw(20) << "과목명" << setw(10) << "과목학점" << setw(10) << "과목등급" << setw(10) << "과목평점" << "\n";
        cout << "====================================================" << "\n";

        for (int j = 0; j < 3; j++)
            cout << setw(20) << student[i].Sub[j].SubName << setw(10) << student[i].Sub[j].Hakjum << setw(10) << student[i].Sub[j].Grade << setw(10) << fixed << setprecision(2) << student[i].Sub[j].GPA << "\n";

        cout << "====================================================" << "\n";
        cout << "                             평균평점" << setw(10) << fixed << setprecision(2) << student[i].AveGPA;
        cout << "\n";
    }
}

void main_menu() {
    cout << "===== 메뉴 =====" << "\n"; 
    cout << "1. 학생 성적 입력" << "\n";
    cout << "2. 전체 학생 성적 보기" << "\n";
    cout << "3. 프로그램 종료" << "\n";
    cout << "\n원하는 기능을 입력하세요 : ";
}
