#pragma once
#include <string>

struct ManufacturedPart {
    int id = 0;
    int productTypeId = 0; 
    std::string serialNumber;
    std::string manufactureDate; 
    double weight = 0.0;        
    std::string status;
};