#include "SQLiteProductTypeRepository.h"
#include <sqlite3.h>
#include <stdexcept>
using namespace std;

SQLiteProductTypeRepository::SQLiteProductTypeRepository(const string& databaseFile)
    : storage_(createStorage(databaseFile)) {
    storage_.on_open = [](sqlite3* db) {
        sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
    };
    storage_.sync_schema();
}

int SQLiteProductTypeRepository::add(const ProductType& productType) {
    return storage_.insert(productType);
}

optional<ProductType> SQLiteProductTypeRepository::findById(int id) {
    return storage_.get_optional<ProductType>(id);
}

vector<ProductType> SQLiteProductTypeRepository::findAll() {
    return storage_.get_all<ProductType>();
}

bool SQLiteProductTypeRepository::update(const ProductType& productType) {
    auto existing = storage_.get_optional<ProductType>(productType.id);
    if (!existing) return false;
    storage_.update(productType);
    return true;
}

bool SQLiteProductTypeRepository::remove(int id) {
    auto existing = storage_.get_optional<ProductType>(id);
    if (!existing) return false;
    storage_.remove<ProductType>(id);
    return true;
}