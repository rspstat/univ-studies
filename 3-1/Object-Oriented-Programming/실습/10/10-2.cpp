#include <iostream>
#include <string>

using namespace std;

class Book{
    string title; int price; int pages;
public:
    Book(string title="", int price=0, int pages=0) {
        this->title = title; this->price = price; this->pages = pages;
    }

    void show() { 
        cout<< title << ' ' << price << "원 " << pages << " 페이지" << endl; 
    }

    string getTitle() {
        return title;
    }

    friend Book& operator+=(Book&, int);
    friend Book& operator-=(Book&, int);
};

Book& operator+=(Book& b,int v){ b.price+=v; return b; }
Book& operator-=(Book& b,int v){ b.price-=v; return b; }

int main(){
    Book a("청춘", 20000, 300), b("미래", 30000, 500);
    a += 500;
    b -= 500;
    a.show(); 
    b.show();

    cout << "2021041017 김규현" << "\n";

    return 0;
}
