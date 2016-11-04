#include <iostream>

using namespace std;

template <typename T> T fact2 (T number);

int main()
{
    int n, k;
    cout << "Zadejte n a k:" << endl;
    cin >> n >> k;
    if (n < 0 || k < 0 || n < k || cin.fail()) {
        cout << "Nespravny vstup." << endl;
    } else {
        cout << "C = " << fact2<long>(n) / (fact2<long>(k) * fact2<long>(n - k)) << endl;
    }
    return 0;
}

template <typename T> T fact2 (T number) {
    number *= (number < 0 ? -1 : 1);
    T temp = 1;
    for (; number + 1 > 1; number--, temp *= number + 1);
    return temp;
}
