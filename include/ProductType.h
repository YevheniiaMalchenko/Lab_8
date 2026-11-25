#pragma once
#include <string>

struct ProductType {
    int id = 0;
    std::string name;
    std::string category;
    double standardWeight = 0.0;
};