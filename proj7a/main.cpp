#include <iostream>

using namespace std;

int main()
{
    int pocet, payout = 8;
    cout << "Zadej pocet navstevniku:" << endl;
    cin >> pocet;
    if (cin.fail() || pocet < 0) {
        cout << "Nespravny vstup." << endl;
        return 0;
    } else {
        if ((int)(pocet * 0.07 * 500) % 10 > 0) pocet = ((pocet * 0.07 * 500) - (int)(pocet * 0.07 * 500) % 10) / 10;
        else pocet *= 0.07 * 50;
        if (pocet >= 0 && pocet < 2000) payout *= 70;
        else if (pocet >= 2000 && pocet < 2500) payout *= 80;
        else if (pocet >= 2500 && pocet < 3000) payout *= 90;
        else if (pocet >= 3000 && pocet < 3500) payout *= 100;
        else payout *= 110;
    }
    cout << "Brigadnik vydela: " << payout << " Kc" << endl;
    return 0;
}
