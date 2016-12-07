#include <iostream>
#include <string>

struct Book {
    std::string name, author_fst, author_sur, genre;
    int year, cost, id;
    Book (std::string name, std::string author_sur, std::string author_fst, std::string genre, int year, int cost, int id) {
        this->name = name;
        this->author_fst = author_fst;
        this->author_sur = author_sur;
        this->genre = genre;
        this->year = year;
        this->cost = cost;
        this->id = id;
    }
    Book () {
    }
};

int main()
{
    Book library[5];
    std::string tmp_a, tmp_b, tmp_c, tmp_d;
    int tmp_e, tmp_f, tmp_g;

    for (int i = 0; i < 5; i++) {
        std::cout << "Zadej nazev knihy, prijmeni autora, jmeno autora, zanr knihy, rok vydani, cenu a id:" << std::endl;
        std::cin >> tmp_a >> tmp_b >> tmp_c >> tmp_d >> tmp_e >> tmp_f >> tmp_g;
        if (std::cin.fail()) {
            /// ERROR NOTIFICATION ?
            return 1;
        }
        library[i] = Book(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, tmp_f, tmp_g);
    }

    std::cout << "Romany jsou:" << std::endl;
    for (int i = 0; i < 5; i++) {
        if (library[i].genre == "roman") std::cout << library[i].name << std::endl;
    }

    std::cout << std::endl << "Knihy s cenou mensi nez 300,- Kc jsou:" << std::endl;
    for (int i = 0; i < 5; i++) {
        if (library[i].cost < 300) std::cout << library[i].name << std::endl;
    }

    std::cout << std::endl << "Prijmeni vsech autoru jsou:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << library[i].author_sur << std::endl;
    }

    return 0;
}
