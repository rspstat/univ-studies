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

---

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

---

#include <iostream>
#include <string>
using namespace std;

class BaseArray {
	int capacity;       // 동적 할당된 메모리 용량
	int *mem;           // 정수 배열을 만들기 위한 메모리 포인터터
protected: 
	BaseArray(int capacity=100) {
		this->capacity = capacity; mem = new int [capacity];
	}
	~BaseArray() { delete [] mem; }
	void put(int index, int val) { mem[index] = val; }
	int get(int index) { return mem[index]; }
	int getCapacity() { return capacity; }
};

class MyQueue : public BaseArray {
	int enindex;
	int deindex;
public:
	MyQueue(int size) : BaseArray(size){ enindex=0; deindex=-1; }
	void enqueue(int n){ 
        put(enindex, n);		
        enindex++; 
    }

	int capacity() { return getCapacity(); }
	int length() { return enindex; }
	int dequeue() { 
        enindex--;	
        deindex++; 
        return get(deindex); 
    }
};

int main() {
	MyQueue mQ(100);
	int n;

	cout << "큐에 삽입할 5개의 정수를 입력하라>> ";
	for(int i=0; i<5; i++) {
		cin >> n;
		mQ.enqueue(n);      // 큐에 삽입입
	}

	cout << "큐의 용량:" << mQ.capacity() << ", 큐의 크기:" << mQ.length() << endl;

	cout << "큐의 원소를 순서대로 제거하여 출력한다>> ";
	while(mQ.length() != 0 ) {
		cout << mQ.dequeue() << ' ';
	}

	cout << endl << "큐의 현재 크기 : " << mQ.length() << endl;
}

---

#include<iostream>
using namespace std;
 
class Shape {
protected:
    string name; // 도형의 이름 
    int width, height; // 도형이 내접하는 사각형의 너비와 높이 
public:
    Shape(string n="", int w=0, int h=0) { name = n; width = w; height = h; }
    virtual double getArea() { return 0; }
    string getName() { return name; }
};
 
class Oval : public Shape {
public:
    Oval(string n, int w, int h) : Shape(n, w, h){;}
    virtual double getArea() { return 3.14 * width * height; }
};
 
class Rect : public Shape {
public:
    Rect(string n, int w, int h) : Shape(n, w, h){;}
    virtual double getArea() { return width * height; }
};
 
class Triangular : public Shape {
public:
     Triangular(string n, int w, int h) : Shape(n, w, h){;}
     virtual double getArea() { return (width * height) / 2; }
};

// double getArea() override {}가 더 좋음
 
int main() {
    Shape *p[3];

    p[0] = new Oval("빈대떡", 10, 20);
    p[1] = new Rect("찰떡", 30, 40);
    p[2] = new Triangular("토스트", 30, 40);

    for(int i=0; i<3; i++)
        cout << p[i]->getName() << " 넓이는 " << p[i]->getArea() << endl;
        
    for(int i=0; i<3; i++) delete p[i];
}   

---

#include <iostream>
using namespace std;

class Calculator {
public:
    virtual int add(int a, int b) = 0;  // 두 정수의 합 리턴
    virtual int subtract(int a, int b) = 0;     // 두 정수의 차 리턴
    virtual double average(int a[], int size) = 0;     // 배열 a의 평균 리턴, size는 배열 크기
};

class GoodCalc : public Calculator {
public:
    int add(int a, int b) { return a + b; }
    int subtract(int a, int b) { return a - b; }
    double average(int a[], int size) {
        double sum = 0;
        for (int i = 0; i < size; i++) {
            sum += a[i];
        }

        return sum / size;
    }
}; 

int main() {
    int a[] = {1,2,3,4,5};
    Calculator *p = new GoodCalc();
    cout << p->add(2, 3) << endl;
    cout << p->subtract(2, 3) << endl;
    cout << p->average(a, 5) << endl;
    delete p;
} 

---

#include <iostream>
using namespace std;

class Calculator {
private:
	void input() {
    	cout << "정수 2 개를 입력하세요>> ";
        cin >> a >> b;
    }
protected:
	int a, b;
    virtual int calc(int a, int b) = 0; // 두 정수의 합 리턴
public:
	void run() {
    	input();
        cout << "계산된 값은 " << calc(a,b) << endl;
    }
};

class Adder : public Calculator {
protected:
    int calc(int a, int b) { return a + b; }
};

class Subtractor : public Calculator {
protected:
    int calc(int a, int b) { return a - b; }
};

int main() {
	Adder adder;
    Subtractor subtractor;
    
    adder.run();
    subtractor.run();
}

---