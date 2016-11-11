#include <iostream>
#include <vector>
#include <algorithm>

// (c) 2016 MARTIN HAFIS HALFAR @ HIRAISHIN SOFTWARE

bool readBoolVector(std::vector<bool>& vect1, std::vector<bool>& vect2, std::istream& stream);
void combineBinaryVector(const std::vector<bool>& vect1, const std::vector<bool>& vect2, std::vector<bool>& out);
void printReversedVector(const std::vector<bool>& vect, std::ostream& stream, bool ignoreZero);

int main() {
    std::vector<bool> set1, set2, set3;
    std::cout << "Zadejte dve binarni cisla:" << std::endl;

    if (!readBoolVector(set1, set2, std::cin) || std::cin.fail() || set1.size() < 1 || set2.size() < 1) {
        std::cout << "Nespravny vstup." << std::endl;
        return 0;
    }

    reverse(set1.begin(), set1.end());
    reverse(set2.begin(), set2.end());
    combineBinaryVector(set1, set2, set3);

    std::cout << "Soucet: ";
    printReversedVector(set3, std::cout, true);
    std::cout << std::endl;

    return 0;
}

bool readBoolVector(std::vector<bool>& vect1, std::vector<bool>& vect2, std::istream& stream) {
    bool input_flag = false;
    char temp = stream.get();

    do {
        if (isspace(temp) && temp != '\n' && !input_flag) {
            input_flag = true;
        } else if (temp == '0' || temp == '1') {
            (input_flag ? vect2 : vect1).push_back(temp == '0' ? false : true);
        } else {
            return false;
        }

    } while ((temp = stream.get()) != '\n');

    return true;
}

void printReversedVector(const std::vector<bool>& vect, std::ostream& stream, bool ignoreZero) {
    for (int i = vect.size() - 1; i >= 0; --i) {
        if (!vect.at(i) && ignoreZero) {
            if (vect.size() == 1 || (!vect.at(0) && i == 0)) {
                stream << '0';
            } else {
                continue;
            }
        } else {
            ignoreZero = false;
            stream << (vect.at(i) ? '1' : '0');
        }
    }
}

void combineBinaryVector(const std::vector<bool>& vect1, const std::vector<bool>& vect2, std::vector<bool>& out) {
    unsigned int i = 0;
    bool a, b, c = false, r = false;

    while (i < vect1.size() || i < vect2.size()) {
        if (i < vect1.size() && i < vect2.size()) {
            a = vect1.at(i);
            b = vect2.at(i);
            r = ((a ^ b) ^ c);
            c = ((a & c) | (a & b) | (b & c));
        } else if (i < vect1.size()) {
            a = vect1.at(i);
            r = (a ^ c);
            c = (a & c);
        } else if (i < vect2.size()){
            b = vect2.at(i);
            r = (b ^ c);
            c = (b & c);
        }
        out.push_back(r);
        ++i;
    }

    if (c) out.push_back(c);
}

// (c) 2016 MARTIN HAFIS HALFAR @ HIRAISHIN SOFTWARE
