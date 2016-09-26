#include <iostream>
#include <string>

using namespace std;

int main()
{
    string name;
    int va;
    cout << "Zadej svoje jmeno (bez diakritiky): ";
    getline(cin, name);
    cout << "Zadej cele cislo: ";
    cin >> va;
    cout << "Ahoj, " << name << '.' << endl;
    cout << va << " x 3 = " << va * 3 << endl;
    cout << va << " / 3 = " << va / 3 << endl;
    return 0;
}
