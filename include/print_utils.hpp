#ifndef PRINT_UTILS_HPP
#define PRINT_UTILS_HPP

#include "common_types.hpp"
#include <string>

std::string getVectorText(const Vector& vec, std::string indent="");
std::string getMatrixText(const Matrix& mat, std::string indent="");

#endif