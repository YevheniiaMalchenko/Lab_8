#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include "ProductType.h"
#include "ManufacturedPart.h"

inline auto createStorage(const std::string& filename) {
    using namespace sqlite_orm;
    return make_storage(filename,
        //Основна таблиця
        make_table("ProductTypes",
            make_column("id", &ProductType::id, primary_key().autoincrement()),
            make_column("name", &ProductType::name, not_null()),
            make_column("category", &ProductType::category, not_null()),
            make_column("standardWeight", &ProductType::standardWeight, not_null())
        ),
        //Залежна таблиця 
        make_table("ManufacturedParts",
            make_column("id", &ManufacturedPart::id, primary_key().autoincrement()),
            make_column("productTypeId", &ManufacturedPart::productTypeId, not_null()),
            make_column("serialNumber", &ManufacturedPart::serialNumber, not_null()),
            make_column("manufactureDate", &ManufacturedPart::manufactureDate, not_null()),
            make_column("weight", &ManufacturedPart::weight, not_null()),
            make_column("status", &ManufacturedPart::status, not_null()),
            foreign_key(&ManufacturedPart::productTypeId).references(&ProductType::id)
        )
    );
}