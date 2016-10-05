#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a, b, c, s, s2;
    cout << "Zadejte delky stran trojuhelnika a, b, c:" << endl;
    cin >> a >> b >> c;
    s = (a + b + c) / 2;
    s2 = (s * (s - a) * (s - b) * (s - c));
    if (a > 0 && b > 0 && c > 0 && s2 > 0) {
        s2 = sqrt(s2);
        cout << "Obsah trojuhelnika je " << s2 << endl;
    } else cout << "Nejedna se o platny trojuhelnik." << endl;
    return 0;
}
