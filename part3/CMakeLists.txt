cmake_minimum_required (VERSION 3.5)
project(qt_iot_blog_samples)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(RTIConnextDDS)
find_package(RTICodeGenerator)
find_package(Qt5 COMPONENTS Core Quick)

add_subdirectory(common)
add_subdirectory(sensor_publisher)
add_subdirectory(sensor_publisher_qml)
add_subdirectory(sensor_subscriber)