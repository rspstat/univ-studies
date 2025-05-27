#include <iostream>

using namespace std;

class Rectangle {
public:
    int width;   // 너비
    int height;  // 높이

    int getArea() {
        return width * height;
    }
};

int main() {
    Rectangle rect;
    rect.width = 3;
    rect.height = 5;
    cout << "사각형의 면적은 " << rect.getArea() << endl;

    return 0;
}