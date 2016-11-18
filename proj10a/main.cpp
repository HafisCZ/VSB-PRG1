#include <iostream>

using namespace std;

bool contains(int* carray, int value, int size) {
    for (int i = 0; i < size; i++) {
        if (carray[i] == value) return true;
    }
    return false;
}

int main() {
    int velA, velB, temp;
    cout << "Zadejte pocet prvku mnoziny A:" << endl;
    cin >> velA;
    if (velA > 0) {
        int* A = new int[velA];
        cout << "Zadejte prvky mnoziny A:" << endl;
        for (int i = 0; i < velA; i++) {
            cin.ignore();
            cin >> temp;
            if (cin.fail() || contains(A, temp, i)) {
                cout << "Nespravny vstup." << endl;
                delete[] A;
                return 0;
            } else {
                A[i] = temp;
            }
        }
        cout << "Zadejte pocet prvku mnoziny B:" << endl;
        cin >> velB;
        if (velB > 0) {
            int* B = new int[velB];
            cout << "Zadejte prvky mnoziny B:" << endl;
            for (int i = 0; i < velB; i++) {
                cin.ignore();
                cin >> temp;
                if (cin.fail() || contains(B, temp, i)) {
                    cout << "Nespravny vstup." << endl;
                    delete[] B;
                    delete[] A;
                    return 0;
                } else {
                    B[i] = temp;
                }
            }
            int k = 0;
            for (int i = 0; i < velA; i++) {
                for (int j = 0; j < velB; j++) {
                    if (A[i] == B[j]) k++;
                    continue;
                }
            }
            cout << "Prunik mnozin:" << endl << "{";
            for (int i = 0; i < velA; i++) {
                for (int j = 0; j < velB; j++) {
                    if (A[i] == B[j]) {
                        cout << A[i] << (--k == 0 ? "" : ", ");
                        continue;
                    }
                }
            }
            cout << "}" << endl;
            delete[] A;
            delete[] B;
            return 0;
        } else {
            delete[] A;
        }
    }
    cout << "Nespravny vstup." << endl;
    return 0;
}
