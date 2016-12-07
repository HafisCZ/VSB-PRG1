#include <iostream>
#include <string>

struct Entry {
    std::string last, first, illness;
    unsigned int warr;
    unsigned long long pnum;

    Entry() {
    }

    Entry(std::string last, std::string first, unsigned long long pnum, std::string illness, unsigned int warr) {
        this->last = last;
        this->first = first;
        this->illness = illness;
        this->pnum = pnum;
        this->warr = warr;
    }
};

int main()
{
    Entry entries[5];
    std::string tmp_a, tmp_b, tmp_c;
    unsigned long long tmp_d;
    unsigned int tmp_e;

    for (int i = 0; i < 5; i++) {
        std::cout << "Zadejte prijmeni, jmeno, rodne cislo, nemoc a zdravotni pojistovnu pacienta:" << std::endl;
        std::cin >> tmp_a >> tmp_b;
        std::cin >> tmp_d;std::cin.ignore();
        std::cin >> tmp_c;
        std::cin >> tmp_e;
        if (std::cin.fail()) {
            /// ERROR NOTIFICATION ?
            return 1;
        }
        entries[i] = Entry(tmp_a, tmp_b, tmp_d, tmp_c, tmp_e);
    }

    for (int i = 0; i < 5; i++) {
        if (entries[i].illness == "tbc") {
            std::cout << "Jmeno a prijmeni pacienta s tbc:" << std::endl;
            std::cout << entries[i].first << ' ' << entries[i].last << std::endl;
        }
        if (entries[i].warr == 211) {
            std::cout << "Jmeno a prijmeni pacientu s pojistovnou 211 je:" << std::endl;
            std::cout << entries[i].first << ' ' << entries[i].last << std::endl;
        }
    }

    std::cout << "Prijmeni vsech pacientu jsou:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << entries[i].last << std::endl;
    }

    return 0;
}
