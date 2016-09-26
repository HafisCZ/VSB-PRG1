#include <iostream>

using namespace std;

int main()
{
    double va, vb;
    cout << "Zadej 1. cislo:" << endl;
    cin >> va;
    cout << "Zadej 2. cislo:" << endl;
    cin >> vb;
    cout << "Zadali jste:" << endl << va << " a " << vb << endl;
    cout << va << " + " << vb << " = " << va + vb << endl;
    cout << va << " - " << vb << " = " << va - vb << endl;
    cout << va << " * " << vb << " = " << va * vb << endl;
    cout << va << " / " << vb << " = " << va / vb << endl;
    return 0;
}
