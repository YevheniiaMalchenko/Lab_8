#include <iostream>
#include <sqlite3.h>
#include <stdexcept>
#include <optional>
#include "Database.h"
#include "ProductType.h"
using namespace std;

// SQLite C API 
int insertRawSQLite(sqlite3* db, const ProductType& pt) {
    const char* sql = "INSERT INTO ProductTypes (name, category, standardWeight) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        throw runtime_error(sqlite3_errmsg(db));

    sqlite3_bind_text(stmt, 1, pt.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, pt.category.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 3, pt.standardWeight);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        string err = sqlite3_errmsg(db);
        sqlite3_finalize(stmt);
        throw runtime_error(err);
    }

    int id = (int)sqlite3_last_insert_rowid(db);
    sqlite3_finalize(stmt);
    return id;
}

optional<ProductType> findRawSQLite(sqlite3* db, int id) {
    const char* sql = "SELECT id, name, category, standardWeight FROM ProductTypes WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        throw runtime_error(sqlite3_errmsg(db));

    sqlite3_bind_int(stmt, 1, id);

    optional<ProductType> result = nullopt;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        ProductType pt;
        pt.id = sqlite3_column_int(stmt, 0);
        pt.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        pt.category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        pt.standardWeight = sqlite3_column_double(stmt, 3);
        result = pt;
    }

    sqlite3_finalize(stmt);
    return result;
}

// sqlite_orm
void runComparisonDemo() {
    cout << "\nQLite C API vs ORM Comparison\n";

    //SQLite C API 
    cout << "\nSQLite C API\n";
    sqlite3* db = nullptr;
    if (sqlite3_open("factory.db", &db) != SQLITE_OK) {
        cerr << "Cannot open DB\n";
        return;
    }
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);

    ProductType pt1{0, "Test Part (Raw)", "Testing", 1.1};
    int rawId = insertRawSQLite(db, pt1);
    cout << "Inserted ID (Raw): " << rawId << "\n";

    auto rawFound = findRawSQLite(db, rawId);
    if (rawFound) {
        cout << "Found (Raw): " << rawFound->name << ", " << rawFound->category << "\n";
    }
    sqlite3_close(db);

    // --- sqlite_orm ---
    cout << "\nsqlite_orm\n";
    auto storage = createStorage("factory.db");
    storage.on_open = [](sqlite3* d) { sqlite3_exec(d, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr); };
    storage.sync_schema();

    ProductType pt2{0, "Test Part (ORM)", "Testing", 2.2};
    int ormId = storage.insert(pt2);
    cout << "Inserted ID (ORM): " << ormId << "\n";

    auto ormFound = storage.get_optional<ProductType>(ormId);
    if (ormFound) {
        cout << "Found (ORM): " << ormFound->name << ", " << ormFound->category << "\n";
    }
}