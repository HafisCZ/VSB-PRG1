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
    for (int i = 2; i <= sqrt(num); i++) if (num % i == 0) return false;
    return true;
}
