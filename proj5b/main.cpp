#include <iostream>

using namespace std;

int main()
{
    int pocet;
    cout << "Zadejte pocet schodu:" <<endl;
    cin >> pocet;
    if (!cin.fail() && pocet > 0) {
        for(int i = 0; i < pocet; i++) {
            for (int j = 0; j <= i; j++) cout << (j < i ? 'X' : '_');
            cout << endl;
        }
    } else {
        cout << "Nespravny vstup." << endl;
    }
    return 0;
}
