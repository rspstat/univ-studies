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

    bool operator!() const { return price == 0; }
};

int main(){
    Book book("벼룩시장", 0, 50);       // 가격은 0
    if(!book) cout << "공짜다" << endl;

    cout << "2021041017 김규현" << "\n";

    return 0;
}
