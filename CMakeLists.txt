cmake_minimum_required(VERSION 3.14)

# ──────────────────────────────
#  Project meta
# ──────────────────────────────
project(CANfusionMQ
        VERSION 0.1.0
        DESCRIPTION "CAN → MQTT bridge"
        LANGUAGES C CXX)

# ──────────────────────────────
#  Compiler dial-ins
# ──────────────────────────────
# C side
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# C++
set(CMAKE_CXX_STANDARD 17)         
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


if(NOT MSVC)
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(CANfusion-MQ
               src/main.cpp)

target_include_directories(CANfusion-MQ
  PRIVATE ${PROJECT_SOURCE_DIR}/include)