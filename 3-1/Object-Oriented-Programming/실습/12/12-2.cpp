#include <iostream>
#include <string>
using namespace std;

class Circle {
	int radius;
public:
	Circle(int radius = 0) { this->radius = radius; }
	int getRadius() { return radius; }
	void setRaidus(int radius) { this->radius = radius; }
	double getArea() { return 3.14 * radius * radius; }
};

class NamedCircle : public Circle {
	int radius;
	string name;
public:
	NamedCircle() {}
	void setName(string name) { this->name = name; }
	string getName() { return name; }
	void show() {
		cout << "반지름이 " << radius << "인 " << name;
	}
};

int main() {
	NamedCircle pizza[5];
	int radius, max;
	string name;

	cout << "5개의 정수 반지름와 원의 이름을 입력하세요." << endl;
	for (int i = 0; i < 5; i++) {
		cout << i + 1 << " >> ";
		cin >> radius >> name;
		pizza[i].setRaidus(radius);
		pizza[i].setName(name);
	}

	max = pizza[0].getRadius();
	int count;

	for (int i = 0; i < 5; i++) {
		if (max < pizza[i].getRadius()) {
			max = pizza[i].getRadius();
			count = i;
		}
	}

	cout << "가장 면적이 큰 피자는 " << pizza[count].getName() << "입니다." << endl;
	cout << "2021041017 김규현" << endl;
}