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

    bool operator==(int p)          const{ return price==p; }
    bool operator==(const string& t)const{ return title==t; }
    bool operator==(const Book& b)  const{ return title==b.title && price==b.price && pages==b.pages; }
};

int main(){
    Book a("명품 C++", 30000, 500), b("고품 C++", 30000, 500);

    // price 비교
    if(a == 30000) cout << "정가 30000원" << endl; 

    // 책 title 비교
    if(a == "명품 C++") cout << "명품 C++ 입니다." << endl;

    // title, price, pages 모두 비교
    if(a == b) cout << "두 책이 같은 책입니다." << endl; 

    cout << "2021041017 김규현" << "\n";

    return 0;
}
