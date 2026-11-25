cmake_minimum_required(VERSION 3.20)
project(Lab_8  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SqliteOrm CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

add_executable(Lab_8  
    src/main.cpp
    src/SQLiteProductTypeRepository.cpp
    src/TestData.cpp
    src/Queries.cpp
    src/TransactionDemo.cpp
    src/ComparisonDemo.cpp
    src/ProductionLine.cpp
    src/StoppedState.cpp
    src/RunningState.cpp
    src/MaintenanceState.cpp
    src/EmergencyState.cpp
)
target_include_directories(Lab_8 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Lab_8 PRIVATE 
    sqlite_orm::sqlite_orm 
    unofficial::sqlite3::sqlite3
)
