#include "TestData.h"
#include "Database.h"
#include <filesystem>
#include <iostream>
#include <vector>
using namespace std;

void prepareTestData() {
    const string dbFile = "factory.db";
    filesystem::remove(dbFile); // Видаляємо стару базу для чистоти
    
    auto storage = createStorage(dbFile);
    storage.on_open = [](sqlite3* db) {
        sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
    };
    storage.sync_schema();
    
    // 5 типів виробів
    vector<ProductType> types = {
        {0, "Gear", "Mechanical", 1.5},
        {0, "Bolt", "Fastener", 0.1},
        {0, "Shaft", "Mechanical", 2.8},
        {0, "Bearing", "Mechanical", 0.5},
        {0, "Housing", "Casing", 4.2}
    };
    vector<int> typeIds;
    for (const auto& t : types) typeIds.push_back(storage.insert(t));
    
    // 15 виготовлених деталей
    vector<ManufacturedPart> parts = {
        {0, typeIds[0], "G-001", "2026-10-01", 1.48, "OK"},
        {0, typeIds[0], "G-002", "2026-10-02", 1.52, "OK"},
        {0, typeIds[0], "G-003", "2026-10-03", 1.50, "Defect"},
        {0, typeIds[1], "B-001", "2026-10-01", 0.11, "OK"},
        {0, typeIds[1], "B-002", "2026-10-02", 0.09, "OK"},
        {0, typeIds[1], "B-003", "2026-10-03", 0.10, "OK"},
        {0, typeIds[2], "S-001", "2026-10-04", 2.79, "OK"},
        {0, typeIds[2], "S-002", "2026-10-05", 2.81, "OK"},
        {0, typeIds[2], "S-003", "2026-10-06", 2.80, "OK"},
        {0, typeIds[3], "R-001", "2026-10-05", 0.49, "OK"},
        {0, typeIds[3], "R-002", "2026-10-06", 0.51, "Defect"},
        {0, typeIds[3], "R-003", "2026-10-07", 0.50, "OK"},
        {0, typeIds[4], "H-001", "2026-10-07", 4.19, "OK"},
        {0, typeIds[4], "H-002", "2026-10-08", 4.21, "OK"},
        {0, typeIds[4], "H-003", "2026-10-09", 4.20, "OK"}
    };
    for (const auto& p : parts) storage.insert(p);
    
    cout << "Test database prepared.\n";
    cout << "Product types: " << storage.count<ProductType>() << "\n";
    cout << "Manufactured parts: " << storage.count<ManufacturedPart>() << "\n";
}