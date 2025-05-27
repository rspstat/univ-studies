#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s;

    cout << "여러 줄의 문자열을 입력하세요. 입력의 끝은 &문자입니다." << endl;

    vector<string> v;
    
    while (1) {
        getline(cin, s);
        if (s == "&") break; // 문자열 끝에 &을 입력 받으면 반복문 종료
        v.push_back(s);  // 벡터에 push
    }

    string f_str, r_str;

    cout << "find: ";
    getline(cin, f_str);

    cout << "replace: ";
    getline(cin, r_str);

    for (int i = 0; i < v.size(); i++) {
        int idx = v[i].find(f_str);
        while (idx != -1) {
            v[i].replace(idx, f_str.length(), r_str);
            idx = v[i].find(f_str, idx + r_str.length());
        }
    }

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }

    return 0;
}
