#include <iostream>

using namespace std;

// 제네릭 함수 add()
template <typename T>
T add(T arr[], int size) {
    T sum = T();  
    for (int i = 0; i < size; i++) 
        sum += arr[i];
    
    return sum;
}

int main() {
    int x[] = {1, 2, 3, 4, 5};
    double d[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};

    cout << "sum of x[] = " << add(x, 5) << endl; // 배열 x의 합 (15)
    cout << "sum of d[] = " << add(d, 6) << endl; // 배열 d의 합 (23.7)

    return 0;
}
