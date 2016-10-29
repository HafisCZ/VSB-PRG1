#include <iostream>
#include <string>

using namespace std;

int main()
{
    char inc;
    long long int i = 1, out = 0;
    string bins = "";
    cout << "Zadejte hexadecimalni cislo:" << endl;
    do {
        cin.get(inc);
        if (inc >= 'a' && inc <= 'f') inc -= 32;
        if (!((inc >= '0' && inc <= '9') || (inc >= 'A' && inc <= 'F') || inc == '\n') || cin.fail() || (inc == '\n' && bins.length() < 1)) {
            cout << "Nespravny vstup." << endl;
            return 0;
        } else if (inc != '\n') bins += inc;
    } while (inc != '\n');

    for (int j = bins.length() - 1; j >= 0; j--) {
        out += ((bins[j] >= '0' && bins[j] <= '9') ? bins[j] - '0' : ((bins[j] >= 'A' && bins[j] <= 'F') ? bins[j] - 'A' + 10 : 0)) * i;
        i *= 16;
    }
    cout << "Desitkove: " << out << endl;

    return 0;
}
