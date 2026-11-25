#pragma once
#include <memory>
#include <string>
#include "IProductionState.h"
using namespace std;

class ProductionLine {
private:
    unique_ptr<IProductionState> state_;
    int producedParts_ = 0;

public:
    explicit ProductionLine(unique_ptr<IProductionState> initialState);
    
    void setState(unique_ptr<IProductionState> newState);
    void start();
    void stop();
    void producePart();
    void showState() const;
    int getProducedParts() const { return producedParts_; }
    void incrementProducedParts() { producedParts_++; }
};