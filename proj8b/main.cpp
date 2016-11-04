#include <iostream>
#include <cmath>

using namespace std;
bool prime(int num);

int main()
{
    int start, stop;
    cout << "Zadejte interval:" << endl;
    cin >> start >> stop;
    if (cin.fail() || stop < start) {
        cout << "Nespravny vstup." << endl;
    } else {
        if (start < 2) start = 2;
        if (stop > 2000000000) stop = 2000000000;
        for (;start <= stop; start++) {
            if (prime(start)) cout << start << endl;
        }
    }
    return 0;
}

bool prime(int num) {
    if (num > 3 && (num % 2 == 0 || num % 3 == 0)) return false;
    else if (num > 7 && num % 7 == 0) return false;
    else if (num > 5 && num % 5 == 0) return false;
    for (int i = 2; i <= sqrt(num); i++) if (num % i == 0) return false;
    return true;
}
