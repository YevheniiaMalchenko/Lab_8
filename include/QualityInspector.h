#pragma once
#include <memory>
#include "IQualityControlStrategy.h"
using namespace std;

class QualityInspector {
private:
    unique_ptr<IQualityControlStrategy> strategy_;

public:
    explicit QualityInspector(unique_ptr<IQualityControlStrategy> strategy)
        : strategy_(move(strategy)) {}

    void setStrategy(unique_ptr<IQualityControlStrategy> strategy) {
        strategy_ = move(strategy);
    }

    string inspect(const ManufacturedPart& part, const ProductType& type) {
        return strategy_->checkQuality(part, type);
    }

    string getStrategyName() const {
        return strategy_->getName();
    }
};