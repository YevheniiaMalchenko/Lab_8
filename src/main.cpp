#include <iostream>
#include "TestData.h"
#include "SQLiteProductTypeRepository.h"
#include "Queries.h"
#include "TransactionDemo.h"
#include "ComparisonDemo.h"
#include "ProductionLine.h"
#include "StoppedState.h"
#include "EmergencyState.h"
#include "QualityInspector.h"
#include "StrictQualityControl.h"
#include "NormalQualityControl.h"
#include "LenientQualityControl.h"
using namespace std;

int main() {
    try {
        cout << "Preparing test data...\n";
        prepareTestData();

        cout << "\nRepository demo...\n";
        SQLiteProductTypeRepository repo("factory.db");
        auto all = repo.findAll();
        cout << "Found " << all.size() << " product types:\n";
        for (const auto& t : all) {
            cout << t.id << " | " << t.name << " | " << t.category << "\n";
        }

        runQueryDemo();
        runTransactionDemo();
        runComparisonDemo();

        cout << "\nSTATE PATTERN DEMO=\n";
        
        ProductionLine line(make_unique<StoppedState>());
        
        //лінія зупинена 
        line.showState();
        line.producePart();
        
        //запускаємо лінію
        line.start();
        line.showState();
        
        //виготовляємо деталі
        line.producePart();
        line.producePart();
        line.producePart();
        
        //зупиняємо лінію
        line.stop();
        line.showState();
        
        //стан аварії
        line.setState(make_unique<EmergencyState>());
        line.showState();
        line.producePart(); //помилка - аварія
        line.start(); //помилка - аварія

        cout << "\nSTRATEGY PATTERN DEMO\n";
        
        ProductType gearType{1, "Gear", "Mechanical", 1.5};
        
        // деталь 1. вага 1.505 (відхилення 0.33%)
        ManufacturedPart part1{0, 1, "G-001", "2026-10-01", 1.505, ""};
        
        // деталь 2:.вага 1.56 (відхилення 4%)
        ManufacturedPart part2{0, 1, "G-002", "2026-10-01", 1.56, ""};
        
        //деталь 3. вага 1.62 (відхилення 8%)
        ManufacturedPart part3{0, 1, "G-003", "2026-10-01", 1.62, ""};

        QualityInspector inspector(make_unique<StrictQualityControl>());
        
        cout << "\nStrategy: " << inspector.getStrategyName() << "\n";
        cout << "Part G-001: " << inspector.inspect(part1, gearType) << endl;
        cout << "Part G-002: " << inspector.inspect(part2, gearType) << endl;
        cout << "Part G-003: " << inspector.inspect(part3, gearType) << endl;

        inspector.setStrategy(make_unique<NormalQualityControl>());
        cout << "\nStrategy: " << inspector.getStrategyName() << "\n";
        cout << "Part G-001: " << inspector.inspect(part1, gearType) << endl;
        cout << "Part G-002: " << inspector.inspect(part2, gearType) << endl;
        cout << "Part G-003: " << inspector.inspect(part3, gearType) << endl;

        inspector.setStrategy(make_unique<LenientQualityControl>());
        cout << "\nStrategy: " << inspector.getStrategyName() << "\n";
        cout << "Part G-001: " << inspector.inspect(part1, gearType) << endl;
        cout << "Part G-002: " << inspector.inspect(part2, gearType) << endl;
        cout << "Part G-003: " << inspector.inspect(part3, gearType) << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}