#pragma once
#include "ManufacturedPart.h"
#include "ProductType.h"
#include <string>
using namespace std;

class IQualityControlStrategy {
public:
    virtual ~IQualityControlStrategy() = default;
    virtual string checkQuality(const ManufacturedPart& part, const ProductType& type) = 0;
    virtual string getName() const = 0;
};