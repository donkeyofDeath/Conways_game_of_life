#include <iostream>
#include <array>
#include "matrix_class/matrix.h"

int main() {

    std::array<std::array<double, 3>, 3> arr = {{{1., 0., 0.},
                                                 {0., 1., 0.},
                                                 {0., 0., 1.}}};

    Matrix<3, 3> matrix(arr);

    matrix.print();

    // std::cout << "Hello, World!" << std::endl;
    return 0;
}
