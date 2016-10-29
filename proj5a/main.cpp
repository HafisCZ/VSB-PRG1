#include <iostream>

using namespace std;

int main()
{
    double a;
    cout << "Zadejte cislo:" << endl;
    cin >> a;
    if (!cin.fail() && ((cin.peek() > '0' && cin.peek() < '9') || cin.peek() == '\n')) {
        cout << a << " : Spravne zadane cislo." << endl;
    } else {
        cout << "Chybne zadani." << endl;
    }
    return 0;
}
