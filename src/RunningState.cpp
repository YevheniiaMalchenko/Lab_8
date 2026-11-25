#include "RunningState.h"
#include "ProductionLine.h"
#include "StoppedState.h"
#include "MaintenanceState.h"
#include <iostream>
using namespace std;

void RunningState::start(ProductionLine& line) {
    cout << "Line is already running" << endl;
}

void RunningState::stop(ProductionLine& line) {
    cout << "Line stopped (Running -> Stopped)" << endl;
    line.setState(make_unique<StoppedState>());
}

void RunningState::producePart(ProductionLine& line) {
    line.incrementProducedParts();
    cout << "Part produced. Total produced: " << line.getProducedParts() << endl;
}