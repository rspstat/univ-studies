#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> str(5);
    
    for (int i = 0; i < 5; i++) {
        cout << "이름 >> ";
        getline(cin, str[i]);
    }

    string ans = str[0];

    for (int i = 0; i < 5; i++) {
        if (str[i] > ans) 
            ans = str[i];
    }

    cout << "사전에서 가장 뒤에 나오는 문자열은 " << ans << "\n";

    return 0;
}
