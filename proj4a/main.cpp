#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a, b, c, s, sv;
    cout << "Zadejte delky stran trojuhelnika a, b, c:" << endl;
    cin >> a >> b >> c;
    s = (a + b + c) / 2;
    sv = sqrt(s * (s - a) * (s - b) * (s - c));
    if (sv > 0) cout << "Obsah trojuhelnika je " << sv << endl;
    else cout << "Nejedna se o platny trojuhelnik." << endl;
    return 0;
}
