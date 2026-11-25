#pragma once
#include "IProductionState.h"
#include <iostream>
using namespace std;

class MaintenanceState : public IProductionState {
public:
    void start(ProductionLine& line) override;
    void stop(ProductionLine& line) override;
    void producePart(ProductionLine& line) override;
    string getName() const override { return "Maintenance"; }
};