#include <iostream>
#include <string>

using namespace std;

class Book {
    string title; int price; int pages;
public:
    Book(string title = "", int price = 0, int pages = 0) {
        this->title = title; this->price = price; this->pages = pages;
    }

    Book& operator+=(int v) { price += v; return *this; }
    Book& operator-=(int v) { price -= v; return *this; }

    void show() const {
        cout << title << ' ' << price << "원 " << pages << " 페이지" << endl;
    }

    string getTitle() {
        return title;
    }
};

int main() {
    Book a("청춘", 20000, 300), b("미래", 30000, 500);
    a += 500;
    b -= 500;
    a.show();
    b.show();

    cout << "2021041017 김규현" << "\n";

    return 0;
}
