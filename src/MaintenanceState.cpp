#include "MaintenanceState.h"
#include "ProductionLine.h"
#include "StoppedState.h"
#include "RunningState.h"
#include <iostream>
using namespace std;

void MaintenanceState::start(ProductionLine& line) {
    cout << "Maintenance finished. Starting (Maintenance -> Running)" << endl;
    line.setState(make_unique<RunningState>());
}

void MaintenanceState::stop(ProductionLine& line) {
    cout << "Maintenance cancelled. (Maintenance -> Stopped)" << endl;
    line.setState(make_unique<StoppedState>());
}

void MaintenanceState::producePart(ProductionLine& line) {
    cout << "ERROR: Cannot produce - line is under maintenance" << endl;
}