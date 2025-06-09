#ifndef COMMON_TYPES_HPP
#define COMMON_TYPES_HPP

#include <vector>

typedef std::vector<std::vector<double> > Matrix;
typedef std::vector<double> Vector;
typedef std::pair<int, int> Dimension;
typedef std::pair<int, double> RowMultiplier;
typedef std::vector<std::pair<int, double> > RowMultVector;

#endif