#include <iostream>

using namespace std;

class Circle {
    int radius; 
public:
    void setRadius(int radius) { this->radius = radius; }
    double getArea() { return 3.14 * radius * radius; }
};

int main() {
    Circle circles[3];
    int count = 0;

    for (int i = 0; i < 3; i++) {
        int r;
        cout << "원 " << i + 1 << "의 반지름 >> ";
        cin >> r;
        circles[i].setRadius(r);
    }

    for (int i = 0; i < 3; i++) {
        if ( circles[i].getArea() > 100 ) {
            count++;
        }
    }

    cout << "면적이 100보다 큰 원 " << count << "개입니다." << "\n";

    return 0;
}