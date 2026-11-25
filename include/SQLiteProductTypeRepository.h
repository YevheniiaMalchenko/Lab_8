#pragma once
#include <string>
#include "IProductTypeRepository.h"
#include "Database.h"
using namespace std;

class SQLiteProductTypeRepository : public IProductTypeRepository {
public:
    explicit SQLiteProductTypeRepository(const string& databaseFile);
    
    int add(const ProductType& productType) override;
    optional<ProductType> findById(int id) override;
    vector<ProductType> findAll() override;
    bool update(const ProductType& productType) override;
    bool remove(int id) override;

private:
    using Storage = decltype(createStorage(""));
    Storage storage_;
};