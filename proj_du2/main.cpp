#include <iostream>
#include <vector>
#include <algorithm>

// (c) 2016 MARTIN HAFIS HALFAR @ HIRAISHIN SOFTWARE

bool readBoolVector(std::vector<bool>& vect1, std::vector<bool>& vect2, std::istream& stream);
void extendCombinaBinaryVector(std::vector<bool>& vect1, std::vector<bool>& vect2, std::vector<bool>& out);
void combineBinaryVector(const std::vector<bool>& vect1, const std::vector<bool>& vect2, std::vector<bool>& out);
void printReversedVector(const std::vector<bool>& vect, std::ostream& stream, bool ignoreZero);

int main() {
    std::vector<bool> set1, set2, set3;
    std::cout << "Zadejte dve binarni cisla:" << std::endl;

    if (!readBoolVector(set1, set2, std::cin) || std::cin.fail() || set1.size() < 1 || set2.size() < 1) {
        std::cout << "Nespravny vstup." << std::endl;
        return 0;
    }

    extendCombinaBinaryVector(set1, set2, set3);

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
            (input_flag ? vect2 : vect1).insert((input_flag ? vect2 : vect1).begin(), temp == '0' ? false : true);
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

void extendCombinaBinaryVector(std::vector<bool>& vect1, std::vector<bool>& vect2, std::vector<bool>& out) {
    bool a, b, c = false;

    if (vect1.size() != vect2.size()) {
        (vect1.size() > vect2.size() ? vect2 : vect1).resize((vect1.size() > vect2.size() ? vect1 : vect2).size(), false);
    }

    for (unsigned int i = 0; i < vect1.size(); i++) {
        a = vect1.at(i);
        b = vect2.at(i);
        out.push_back((a ^ b) ^ c);
        c = ((a & b) | (a & c) | (b & c));
    }

    if (c) out.push_back(c);
}

void combineBinaryVector(const std::vector<bool>& vect1, const std::vector<bool>& vect2, std::vector<bool>& out) {
    unsigned int i = 0, vect1_size = vect1.size(), vect2_size = vect2.size();
    bool a, b, c = false, r = false;

    while (i < vect1_size || i < vect2_size) {
        if (i < vect1_size) a = vect1.at(i);
        if (i < vect2_size) b = vect2.at(i);
        r = (i < vect1_size && i < vect2_size ? a ^ b : (vect1_size < vect2_size ? b : a)) ^ c;
        c = (i < vect1_size && i < vect2_size ? ((a & b) | (b & c) | (a & c)) : (vect1_size < vect2_size ? (b & c) : (a & c)));
        out.push_back(r);
        ++i;
    }

    if (c) out.push_back(c);
}

// (c) 2016 MARTIN HAFIS HALFAR @ HIRAISHIN SOFTWARE
