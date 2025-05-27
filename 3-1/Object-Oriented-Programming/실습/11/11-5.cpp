11-5번 코드가 그대로 실행되면 출력결과:
생성자 호출: Charlie
복사 생성자 호출: Charlie (얕은 복사)
[main] b 이름 변경 전: 이름: Charlie
[main] b 이름 변경 후: 이름: Bob
[main] a 이름 확인: 이름: Bob
복사 생성자 호출: Bob (얕은 복사)
[introduce 함수] 이름: Bob
[introduce 함수 변경 후] 이름: Alex
소멸자 호출: Alex
생성자 호출: Temporary
복사 생성자 호출: Temporary (얕은 복사)
소멸자 호출: Temporary
소멸자 호출: Temporary        // c  파괴
소멸자 호출: Alex             // b  파괴
소멸자 호출: Alex             // a  파괴

출력이 왜 그렇게 되는지 메모리 동작 설명:
# 11-5 원본 코드의 메모리 동작 (얕은 복사 기준)

1. Person a("Charlie")
   (a) new char[8] 로 "Charlie\0" 저장
   (b) a.name → 버퍼1 주소

2. Person b = a   // 복사 생성자, 얕은 복사
   (a) b.name = a.name  (버퍼1 공유)

3. b.changeName("Bob")
   (a) strcpy(버퍼1, "Bob")  → 버퍼1 내용이 "Bob\0"로 바뀜
   (b) a.name, b.name 모두 "Bob"을 가리킴

4. introduce(a)   // 값 전달 → 또 얕은 복사
   4-1. Person p = a
        (a) p.name = a.name  (버퍼1 다시 공유)
   4-2. p.changeName("Alex")
        (a) strcpy(버퍼1, "Alex")  → a, b, p 모두 "Alex"
   4-3. p 소멸
        (a) delete[] 버퍼1   → 첫 번째 해제, a와 b는 덩글링 포인터 됨

5. Person c = createPerson()
   5-1. Person temp("Temporary")
        (a) new char[10] 로 "Temporary\0" 저장
        (b) temp.name → 버퍼2 주소
   5-2. return temp;   // RVO 미적용 시 얕은 복사
        (a) c.name = temp.name  (버퍼2 공유)
   5-3. temp 소멸
        (a) delete[] 버퍼2   → 두 번째 해제, c는 덩글링

6. main 종료
   (a) c 소멸  → delete[] 버퍼2  (세 번째 해제, double free)
   (b) b 소멸  → delete[] 버퍼1  (네 번째 해제, double free)
   (c) a 소멸  → delete[] 버퍼1  (다섯 번째 해제, triple free → 크래시 가능)


수정된 코드:
#include <iostream>
#include <cstring>
using namespace std;

class Person {
    char* name;
public:
    Person(const char* n) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
    Person(const Person& p) {
        name = new char[strlen(p.name) + 1];
        strcpy(name, p.name);
    }
    Person& operator=(const Person& p) {
        if (this != &p) {
            delete[] name;
            name = new char[strlen(p.name) + 1];
            strcpy(name, p.name);
        }
        return *this;
    }
    ~Person() { delete[] name; }

    void changeName(const char* newName) {
        delete[] name;
        name = new char[strlen(newName) + 1];
        strcpy(name, newName);
    }
    void show() const { cout << "이름: " << name << endl; }
};

void introduce(const Person& p) {
    cout << "[introduce 함수] ";
    p.show();
}

Person createPerson() {
    return Person("Temporary");
}

int main() {
    Person a("Charlie");
    Person b = a;
    cout << "[main] b 이름 변경 전: ";
    b.show();
    b.changeName("Bob");
    cout << "[main] b 이름 변경 후: ";
    b.show();
    cout << "[main] a 이름 확인: ";
    a.show();
    introduce(a);
    Person c = createPerson();
}
