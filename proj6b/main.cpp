#include <iostream>
#include <string>

using namespace std;

int main()
{
    char inc;
    long long int i = 1, out = 0;
    string bins = "";
    cout << "Zadej cislo ve dvojkove soustave:" << endl;
    do {
        cin.get(inc);
        if (!(inc == '1' || inc == '0' || inc == '\n') || cin.fail() || (inc == '\n' && bins.length() < 1)) {
            cout << "Nespravny vstup." << endl;
            return 0;
        } else if (inc != '\n') bins += inc;
    } while (inc != '\n');

    for (int j = bins.length() - 1; j >= 0; j--) {
        out += (bins[j] - '0') * i;
        i *= 2;
    }
    cout << "Desitkove cislo je: " << out << endl;

    return 0;
}
