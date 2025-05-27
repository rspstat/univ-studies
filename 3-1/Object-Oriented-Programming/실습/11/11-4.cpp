#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Book {
    char* title;
    int price;
public:
    Book(const char* title, int price);
    ~Book();
    void set(const char* title, int price);
    void show() const { cout << title << ' ' << price << "원" << endl; }
};

Book::Book(const char* title, int price) {
    this->title = new char[strlen(title) + 1];
    strcpy(this->title, title);
    this->price = price;
}

Book::~Book() { delete[] title; }

void Book::set(const char* title, int price) {
    this->title = new char[strlen(title) + 1];
    strcpy(this->title, title);
    this->price = price;
}

int main() {
    Book cpp("명품C++", 10000);
    Book java = cpp;
    java.set("명품자바", 12000);
    cpp.show();
    java.show();

    cout << "\n2021041017 김규현" << endl;
}
