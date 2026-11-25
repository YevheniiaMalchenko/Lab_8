#include "ProductionLine.h"
#include <iostream>
using namespace std;

ProductionLine::ProductionLine(unique_ptr<IProductionState> initialState)
    : state_(move(initialState)) {}

void ProductionLine::setState(unique_ptr<IProductionState> newState) {
    state_ = move(newState);
}

void ProductionLine::start() { state_->start(*this); }
void ProductionLine::stop() { state_->stop(*this); }
void ProductionLine::producePart() { state_->producePart(*this); }

void ProductionLine::showState() const {
    cout << "Current state: " << state_->getName() << endl;
}