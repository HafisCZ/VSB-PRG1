#include <iostream>
#include <string>

void tolower(std::string& str) {
    for (unsigned int i = 0; i < str.length(); i++) {
        str[i] = (str[i] >= 'A' && str[i] <= 'Z' ? str[i] + 32 : str[i]);
    }
}

int main()
{
    unsigned int iter = 0;
    std::string word[3], str;

    std::cout << "Zadejte tri slova" << std::endl;
    std::getline(std::cin, str);
    for (unsigned int i = 0; i < str.length(); i++) {
        if (isspace(str[i])) {
            if (++iter > 2) {
                break;
            }
        } else {
            word[iter] += str[i];
        }
    }

    if (std::cin.fail() || iter != 2) {
        std::cout << "Nespravny vstup" << std::endl;
        return 0;
    }

    tolower(word[0]);
    tolower(word[1]);
    tolower(word[2]);
    std::cout << "Slovo1 a slovo2 " << (word[0] == word[1] ? "jsou" : "nejsou") << " stejna." << std::endl;
    std::cout << "Slovo1 a slovo3 " << (word[0] == word[2] ? "jsou" : "nejsou") << " stejna." << std::endl;
    std::cout << "Slovo2 a slovo3 " << (word[1] == word[2] ? "jsou" : "nejsou") << " stejna." << std::endl;

    for (unsigned int i = 0; i < 3; i++) {
        std::cout << "Pocet znaku ve slovo" << i << " je: " << word[i].size() << std::endl;
    }


    return 0;
}
