#pragma once
#include "IQualityControlStrategy.h"
#include <cmath>
using namespace std;

class LenientQualityControl : public IQualityControlStrategy {
public:
    string checkQuality(const ManufacturedPart& part, const ProductType& type) override {
        double deviation = abs(part.weight - type.standardWeight) / type.standardWeight;
        if (deviation <= 0.10) return "OK";
        return "Defect";
    }
    string getName() const override { return "Lenient (+-10%)"; }
};