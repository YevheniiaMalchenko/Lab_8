#include "TransactionDemo.h"
#include "Database.h"
#include <iostream>
#include <stdexcept>
using namespace std;
using namespace sqlite_orm;

void runTransactionDemo() {
    auto storage = createStorage("factory.db");
    storage.on_open = [](sqlite3* db) {
        sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
    };
    storage.sync_schema();

    cout << "\nTRANSACTION DEMONSTRATION\n";

    auto eqBefore = storage.count<ProductType>();
    auto partBefore = storage.count<ManufacturedPart>();
    cout << "\nBefore transaction:\n";
    cout << "Product types: " << eqBefore << "\n";
    cout << "Manufactured parts: " << partBefore << "\n";

    cout << "\nSuccessful transaction\n";
    bool committed = storage.transaction([&]() {
        ProductType newType{0, "Valve", "Plumbing", 1.2};
        int typeId = storage.insert(newType);
        cout << "Inserted product type ID: " << typeId << "\n";

        ManufacturedPart newPart{0, typeId, "V-001", "2026-10-20", 1.18, "OK"};
        storage.insert(newPart);
        cout << "Inserted part V-001\n";

        return true; 
    });

    cout << "Transaction committed: " << boolalpha << committed << "\n";
    cout << "Product types after commit: " << storage.count<ProductType>() << "\n";
    cout << "Parts after commit: " << storage.count<ManufacturedPart>() << "\n";

    cout << "\nFailed transaction (ROLLBACK)\n";
    auto countBeforeRollback = storage.count<ProductType>();

    try {
        storage.transaction([&]() {
            ProductType badType{0, "Piston", "Mechanical", 2.5};
            int badTypeId = storage.insert(badType);
            cout << "Inserted bad product type ID: " << badTypeId << "\n";

            ManufacturedPart invalidPart{0, -1, "P-001", "2026-10-21", 2.45, "OK"};
            storage.insert(invalidPart);
            cout << "This should not be printed!\n";
            return true;
        });
    } catch (const exception& ex) {
        cout << "Transaction failed: " << ex.what() << "\n";
        cout << "Changes rolled back.\n";
    }

    cout << "\nProduct types after failed transaction: " << storage.count<ProductType>() << "\n";
    cout << "(Should be same as before: " << countBeforeRollback << ")\n";

    auto pistons = storage.get_all<ProductType>(
        where(c(&ProductType::name) == "Piston")
    );
    cout << "Piston exists: " << boolalpha << !pistons.empty() << " (should be false)\n";
}