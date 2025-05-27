#include <iostream>

using namespace std;

int main() {
    int i1 = 10;
    int i2 = 20;

    // A
    const int* pInt1;
    pInt1 = &i1;
    // *pInt1 = 30;  // const로 선언된 포인터는 값을 변경할 수 없음

    // B
    int* const pInt2 = &i1;
    // pInt2 = &i2;  // 포인터 자체가 const이므로 주소 변경 불가
    *pInt2 = 50;     // 가리키는 값은 변경 가능

    // C
    const int* const p = &i2;
    // p = &i1;       // 주소 변경 불가
    // *p = 40;       // 값 변경 불가

    cout << "소프트웨어학과 2021041017 김규현" << "\n";

    return 0;
}
