cmake_minimum_required (VERSION 3.5)

project(sensor_subscriber LANGUAGES CXX)

add_executable(sensor_subscriber
  "main.cpp"
  )

target_link_libraries(sensor_subscriber
  common
  Qt5::Core
)