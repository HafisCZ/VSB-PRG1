#include <iostream>

using namespace std;

int main()
{
    double vys = 0, rec;
    cout << "Zadavejte cisla, posledni bude 1000:" << endl;
    while (rec != 1000) {
        cin >> rec;
        vys += rec;
    }
    cout << "Vysledek souctu cisel je: " << vys << endl;
    return 0;
}
