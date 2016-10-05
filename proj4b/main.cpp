#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a, b, c, d;
    cout << "Zadejte parametry:" << endl;
    cin >> a >> b >> c;
    d = b * b - 4 * a * c;
    if (d >= 0 && a != 0) {
        d = sqrt(d);
        cout << "Koren 1: " << ((-b - d) / (2 * a)) << endl;
        cout << "Koren 2: " << ((-b + d) / (2 * a)) << endl;
    } else cout << "Rovnice nema reseni v R." << endl;
    return 0;
}
