cmake_minimum_required (VERSION 3.5)

project(sensor_publisher LANGUAGES CXX)

add_executable(sensor_publisher
  "main.cpp"
  )

target_link_libraries(sensor_publisher
  common
  Qt5::Core
)