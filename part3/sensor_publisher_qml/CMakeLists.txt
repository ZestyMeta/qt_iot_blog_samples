cmake_minimum_required (VERSION 3.5)

project(sensor_publisher_qml LANGUAGES CXX)

add_executable(sensor_publisher_qml
  "main.cpp"
  "sensorinformation.cpp"
  "qml.qrc"
 )

target_link_libraries(sensor_publisher_qml
  common
  Qt5::Core
  Qt5::Quick
)