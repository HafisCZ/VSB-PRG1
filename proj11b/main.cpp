#include <iostream>
#include <cmath>

#define _USE_MATH_DEFINES

int main()
{
    int iters;
    double px, py, pfi, dx, v, o;
    std::cout << std::fixed;
    std::cout.precision(2);
    std::cin >> iters;
    if (iters < 1 || std::cin.fail()) {
        std::cout << "Nespravny vstup." << std::endl;
        return 0;
    }
    std::cin >> px >> py >> pfi >> dx >> v >> o;
    if (std::cin.fail()) {
        std::cout << "Nespravny vstup." << std::endl;
        return 0;
    }
    for (int i = 0; i < iters; i++) {
        px += v * dx * cos(pfi);
        py += v * dx * sin(pfi);
        pfi = fmod(pfi + dx * o, 2 * M_PI);
        std::cout << "x: " << px << ", y: " << py << ", fi: " << pfi << std::endl;
    }
    return 0;
}
