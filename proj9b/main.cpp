#include <iostream>
#include <string>

unsigned int areInRange(std::string input, char start, char end);
unsigned int areSpecial(std::string input);

int main()
{
    bool succeded = false;
    std::string password;
    std::cin >> password;

    succeded = ((password.size() >= 5 && areInRange(password, '0', '9') >= 1 && (areInRange(password, 'a', 'z') >= 1 || areInRange(password, 'A', 'Z') >= 1) && areSpecial(password)) ? true : false);

    std::cout << "Heslo " << (succeded ? "" : "ne") << "splnuje pozadavky." << std::endl;
    return 0;
}

unsigned int areInRange(std::string input, char start, char end) {
    unsigned int counter = 0;
    for (unsigned int i = 0; i < input.size(); i++) {
        if (input[i] >= start && input[i] <= end) {
            counter++;
        }
    }
    return counter;
}

unsigned int areSpecial(std::string input) {
    unsigned int counter = 0;
    for (unsigned int i = 0; i < input.size(); i++) {
        if (!((input[i] >= 'a' && input[i] <= 'Z') || (input[i] >= 'A' && input[i] <= 'Z') || std::isalnum(input[i]))) {
            counter++;
        }
    }
    return counter;
}
