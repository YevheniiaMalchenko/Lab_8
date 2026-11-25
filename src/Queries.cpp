#include "Queries.h"
#include "Database.h"
#include <iostream>
#include <vector>
using namespace std;
using namespace sqlite_orm;

void runQueryDemo() {
    auto storage = createStorage("factory.db");
    storage.sync_schema();

    cout << "\nQUERY DEMONSTRATION\n";

    //Фільтрація: деталі зі статусом "Defect"
    cout << "\n1. Defective parts:\n";
    auto defects = storage.get_all<ManufacturedPart>(
        where(c(&ManufacturedPart::status) == "Defect")
    );
    for (const auto& p : defects) {
        cout << p.id << " | " << p.serialNumber << " | " << p.status << "\n";
    }

    //Сортування: всі деталі за вагою (спадання) + обмеження (топ-3)
    cout << "\n2. Top 3 heaviest parts:\n";
    auto heaviest = storage.get_all<ManufacturedPart>(
        order_by(&ManufacturedPart::weight).desc(),
        limit(3)
    );
    for (const auto& p : heaviest) {
        cout << p.id << " | " << p.serialNumber << " | " << p.weight << " kg\n";
    }

    // Агрегація: загальна кількість, сума та середня вага
    cout << "\n3. Aggregates:\n";
    auto totalCount = storage.count<ManufacturedPart>();
    auto totalWeight = storage.sum(&ManufacturedPart::weight);
    auto avgWeight = storage.avg(&ManufacturedPart::weight);
    cout << "Total parts: " << totalCount << "\n";
    cout << "Total weight: " << (totalWeight != nullptr ? *totalWeight : 0.0) << " kg\n";
    cout << "Average weight: " << avgWeight << " kg\n";

    //Групування: сумарна вага деталей за типами виробів
    cout << "\n4. Total weight by product type:\n";
    auto weightByType = storage.select(
        columns(
            &ManufacturedPart::productTypeId,
            sum(&ManufacturedPart::weight)
        ),
        group_by(&ManufacturedPart::productTypeId)
    );
    for (const auto& [typeId, totalW] : weightByType) {
        cout << "Type ID: " << typeId << " | Total weight: " << (totalW != nullptr ? *totalW : 0.0) << " kg\n";

    }

    //JOIN: назва типу + серійний номер деталі + статус
    cout << "\n5. JOIN: Parts with type names:\n";
    auto joined = storage.select(
        columns(
            &ProductType::name,
            &ManufacturedPart::serialNumber,
            &ManufacturedPart::status
        ),
        inner_join<ManufacturedPart>(
            on(c(&ProductType::id) == &ManufacturedPart::productTypeId)
        ),
        order_by(&ManufacturedPart::id)
    );
    for (const auto& [name, serial, status] : joined) {
        cout << name << " | " << serial << " | " << status << "\n";
    }
}