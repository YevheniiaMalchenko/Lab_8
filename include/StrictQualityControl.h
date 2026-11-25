#pragma once
#include "IQualityControlStrategy.h"
#include <cmath>
using namespace std;

class StrictQualityControl : public IQualityControlStrategy {
public:
    string checkQuality(const ManufacturedPart& part, const ProductType& type) override {
        double deviation = abs(part.weight - type.standardWeight) / type.standardWeight;
        if (deviation <= 0.01) return "OK";
        return "Defect";
    }
    string getName() const override { return "Strict (+-1%)"; }
};