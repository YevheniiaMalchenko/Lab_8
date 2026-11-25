#include "EmergencyState.h"
#include "ProductionLine.h"
#include "StoppedState.h"
#include <iostream>
using namespace std;

void EmergencyState::start(ProductionLine& line) {
    cout << "ERROR: Cannot start - emergency! Fix first!" << endl;
}

void EmergencyState::stop(ProductionLine& line) {
    cout << "Emergency resolved. (Emergency -> Stopped)" << endl;
    line.setState(make_unique<StoppedState>());
}

void EmergencyState::producePart(ProductionLine& line) {
    cout << "ERROR: Cannot produce - emergency!" << endl;
}