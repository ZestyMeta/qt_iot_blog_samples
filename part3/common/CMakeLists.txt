cmake_minimum_required (VERSION 3.5)

project(common LANGUAGES CXX)

set(GENERATED_SOURCES
  ${PROJECT_BINARY_DIR}/sensor.cxx
  ${PROJECT_BINARY_DIR}/sensorImpl.cxx
  ${PROJECT_BINARY_DIR}/sensorImplPlugin.cxx
 )

add_custom_command(OUTPUT ${GENERATED_SOURCES}
  COMMAND ${RTICODEGEN} -language C++11 -d ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/sensor.idl
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  DEPENDS ${PROJECT_SOURCE_DIR}/sensor.idl
)

set_source_files_properties(${GENERATED_SOURCES} PROPERTIES GENERATED TRUE)

add_library(common
  ${GENERATED_SOURCES}
)

target_link_libraries(common
  PUBLIC ${CONNEXTDDS_CPP2_API_LIBRARIES_RELEASE_SHARED}
)

target_include_directories(common
  PUBLIC ${PROJECT_BINARY_DIR}
  PUBLIC ${PROJECT_SOURCE_DIR}
  PUBLIC ${CONNEXTDDS_INCLUDE_DIRS}
)

target_compile_definitions(common
  PUBLIC RTI_UNIX
  PUBLIC RTI_LINUX
  PUBLIC RTI_64BIT
)