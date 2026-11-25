#include "StoppedState.h"
#include "ProductionLine.h"
#include "RunningState.h"
#include "MaintenanceState.h"
#include <iostream>
using namespace std;

void StoppedState::start(ProductionLine& line) {
    cout << "Line started (Stopped -> Running)" << endl;
    line.setState(make_unique<RunningState>());
}

void StoppedState::stop(ProductionLine& line) {
    cout << "Line is already stopped" << endl;
}

void StoppedState::producePart(ProductionLine& line) {
    cout << "ERROR: Cannot produce - line is stopped" << endl;
}