cmake_minimum_required(VERSION 3.14)
project(game_of_life)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/home/matlle/Qt/5.12.5/gcc_64/lib/cmake")

set(SOURCE_FILES main.cpp sources/MainWindow.cpp headers/MainWindow.h headers/GridView.h sources/GridView.cpp headers/CellItem.h sources/CellItem.cpp)
add_executable(game_of_life ${SOURCE_FILES})

target_link_libraries(game_of_life Qt5::Core)
target_link_libraries(game_of_life Qt5::Widgets)