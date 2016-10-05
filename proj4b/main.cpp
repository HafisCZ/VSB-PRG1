#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a, b, c, d;
    cout << "Zadejte parametry:" << endl;
    cin >> a >> b >> c;
    d = sqrt(b * b - 4 * a * c);
    cout << "Koren 1: " << (-b - d) / 2 << endl;
    cout << "Koren 2: " << (-b + d) / 2 << endl;
    return 0;
}
