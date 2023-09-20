#include "sort_complex.h"
#include <algorithm>

void sort_complex(std::vector<Complex>& data) {
    std::sort(data.begin(), data.end(),  {
        return a.abs() < b.abs();
    });
}
