#include <iostream>
#include "Operations.h"

int main() {
    int a = 5;
    int b = 10;

    std::cout << "Sum: " << add(a, b) << std::endl;
    std::cout << "Difference: " << subtract(a, b) << std::endl;

    return 0;
}
