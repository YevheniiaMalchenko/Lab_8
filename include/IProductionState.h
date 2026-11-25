#pragma once
#include <string>
using namespace std;

class ProductionLine; 

class IProductionState {
public:
    virtual ~IProductionState() = default;
    virtual void start(ProductionLine& line) = 0;
    virtual void stop(ProductionLine& line) = 0;
    virtual void producePart(ProductionLine& line) = 0;
    virtual string getName() const = 0;
};