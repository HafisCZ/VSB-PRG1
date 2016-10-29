#include <iostream>
#include <cmath>

#define _USE_MATH_DEFINES

using namespace std;

int main()
{
    char inp;
    double a, b;
    cout << std::fixed;
    cout.precision(4);
    cout << "Zadejte rovinny obrazec, jehoz obsah a obvod chcete spocitat: a - ctverec, b - obdelnik, c - kruh" << endl;
    cin >> inp;
    cin.ignore();
    if (inp == 'a') {
        cout << "Zadejte stranu ctverce:" << endl;
        cin >> a;
        if (a > 0 && !cin.fail()) {
                cout << "Obsah ctverce je: " << a * a << endl << "Obvod ctverce je: " << 4.0 * a << endl;
        return 0;
        }
    } else if (inp == 'b') {
        cout << "Zadejte strany obdelniku:" << endl;
        cin >> a >> b;
        if (a > 0 && b > 0 && !cin.fail()) {
            cout << "Obsah obdelniku je: " << a * b << endl << "Obvod obdelniku je: " << 2.0 * (a + b) << endl;
            return 0;
        }
    } else if (inp == 'c') {
        cout << "Zadejte polomer kruznice:" << endl;
        cin >> a;
        if (a > 0 && !cin.fail()) {
            cout << "Obsah kruznice je: " << M_PI * a * a << endl << "Obvod kruznice je: " << 2.0 * M_PI * a << endl;
            return 0;
        }
    }
    cout << "Nespravny vstup." << endl;
    return 0;
}
