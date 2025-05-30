#include<iostream>
using namespace std;
 
class Circle{
    int radius;
public:
    Circle(int radius=0) { this->radius = radius; }
    int getRadius() { return radius; }
    void setRadius(int radius) { this->radius = radius; }
    double getArea() { return 3.14*radius*radius; }
};
 
class NameCircle : public Circle{
    string name;
public:
    NameCircle(int radius, string name){ 
        setRadius(radius);
        this->name = name;
    }

    void show() {
        cout << "반지름이 " << getRadius() << "인 " << this->name; 
    }
};
 
int main() {
    NameCircle waffle(3, "waffle"); // 반지름이 3이고 이름이 waffle인 원
    waffle.show();
}