cmake_minimum_required(VERSION 3.15)

option(BUILD_FOR_PI "Pi için cross-compile" OFF)

if(BUILD_FOR_PI)
  message(STATUS ">>> Cross derleme: Pi hedefleniyor")
  set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchains/raspi.cmake" CACHE STRING "" FORCE)
else()
  message(STATUS ">>> Native derleme: Host makine")
endif()

project(CANfusion-MQ LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

find_package(PkgConfig REQUIRED)
pkg_search_module(SOCKETCAN REQUIRED libsocketcan)

# Paho kısmı kaldırıldı
# list(APPEND CMAKE_PREFIX_PATH "/usr/local/lib/cmake/eclipse-paho-mqtt-c")
# find_package(eclipse-paho-mqtt-c CONFIG REQUIRED)
# if(BUILD_FOR_PI)
#   pkg_search_module(PAHO REQUIRED libpaho-mqtt3c)
# endif()

add_executable(CANfusion-MQ ${SOURCES})

target_include_directories(CANfusion-MQ PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(CANfusion-MQ PRIVATE
  ${SOCKETCAN_LIBRARIES}
  # eclipse-paho-mqtt-c::paho-mqtt3c
  pthread
)
