#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double ax, ay, bx, by, vektu;
    cout << "Zadejte souradnice bodu A a B:" << endl;
    cin >> ax >> ay >> bx >> by;
    cout << "X-ova souradnice stredu S je: " << (ax + bx) / 2 << endl;
    cout << "Y-ova souradnice stredu S je: " << (ay + by) / 2 << endl;
    vektu = sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
    cout << "Smerovy vektor u ma delku: " << vektu << endl;
    cout << "Polomer kruznice r ma hodnotu: " << vektu / 2 << endl;
    return 0;
}
