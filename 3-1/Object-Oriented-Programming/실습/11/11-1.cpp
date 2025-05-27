#include <iostream>
using namespace std;

class Circle {
private:
    int radius;
public:
    Circle() { radius = 1; }
    Circle(int radius) { this->radius = radius; }
    double getArea() { return 3.14 * radius * radius; }
};

static void swap(Circle& a, Circle& b) {
    Circle temp = a;
    a = b;
    b = temp;
}

int main() {
    Circle A(2), B(3);
    cout << "A의 면적 = " << A.getArea() << "  B의 면적 = " << B.getArea() << endl;
    swap(A, B);
    cout << "A의 면적 = " << A.getArea() << "  B의 면적 = " << B.getArea() << endl;

    cout << "\n2021401017 김규현" << endl;
}
