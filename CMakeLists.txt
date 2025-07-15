cmake_minimum_required(VERSION 3.15)
project(CANfusion-MQ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
)
find_package(PkgConfig REQUIRED)
pkg_search_module(SOCKETCAN REQUIRED libsocketcan)

# ---- use Paho’s CMake config ----
list(APPEND CMAKE_PREFIX_PATH "/usr/local/lib/cmake/eclipse-paho-mqtt-c")
find_package(eclipse-paho-mqtt-c CONFIG REQUIRED)

add_executable(CANfusion-MQ
  ${SOURCES}
)

target_link_libraries(CANfusion-MQ PRIVATE
  ${SOCKETCAN_LIBRARIES}
  eclipse-paho-mqtt-c::paho-mqtt3c
  pthread
)

target_include_directories(CANfusion-MQ
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)