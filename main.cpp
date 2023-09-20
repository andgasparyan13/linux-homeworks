#include "complex.h"
#include "sort_complex.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<Complex> data = {Complex(3, 4), Complex(5, 12), Complex(8, 15)};
    
    std::cout << "Before sorting:\n";
    for (const auto& c : data)
        std::cout << c.abs() << '\n';
    
    sort_complex(data);
    
    std::cout << "\nAfter sorting:\n";
    for (const auto& c : data)
        std::cout << c.abs() << '\n';
    
    return 0;
}
