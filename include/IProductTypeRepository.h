#pragma once
#include <optional>
#include <vector>
#include "ProductType.h"
using namespace std;

class IProductTypeRepository {
public:
    virtual ~IProductTypeRepository() = default;
    
    virtual int add(const ProductType& productType) = 0;
    virtual optional<ProductType> findById(int id) = 0;
    virtual vector<ProductType> findAll() = 0;
    virtual bool update(const ProductType& productType) = 0;
    virtual bool remove(int id) = 0;
};