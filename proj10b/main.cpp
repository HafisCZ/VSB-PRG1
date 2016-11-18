#include <iostream>
#include <cmath>

using namespace std;

double vypocist(double *v1, double *v2, int velikost) {
    double scalar = 0, v1sq = 0, v2sq = 0;
    for (int i = 0; i < velikost; i++) {
        scalar += v1[i] * v2[i];
        v1sq += v1[i] * v1[i];
        v2sq += v2[i] * v2[i];
    }
    return scalar / (sqrt(v1sq) * sqrt(v2sq));
}

int main()
{
    int velikost;
    cin >> velikost;

    cout << fixed;
    cout.precision(3);

    if (velikost > 0 && !cin.fail()) {
        double* v1 = new double[velikost];
        double* v2 = new double[velikost];
        for (int i = 0; i < velikost; i++) {
            cin >> v1[i];
            if (cin.fail()) {
                cout << "Nespravny vstup." << endl;
                delete[] v1;
                delete[] v2;
                return 0;
            }
        }
        for (int i = 0; i < velikost; i++) {
            cin >> v2[i];
            if (cin.fail()) {
                cout << "Nespravny vstup." << endl;
                delete[] v1;
                delete[] v2;
                return 0;
            }
        }
        cout << "CSM: " << vypocist(v1, v2, velikost) << endl;
        delete[] v1;
        delete[] v2;
        return 0;
    }

    cout << "Nespravny vstup." << endl;
    return 0;
}
