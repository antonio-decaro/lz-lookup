cmake_minimum_required(VERSION 3.17)
project(LevelZeroLookup VERSION 0.1 LANGUAGES CXX)
include_directories(include)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(LevelZero REQUIRED)

# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsycl -fsycl-targets=intel_gpu_acm_g10")

add_executable(lz_info src/sub_devices.cpp)
target_link_libraries(lz_info PRIVATE LevelZero::LevelZero)
target_compile_features(lz_info PRIVATE cxx_std_17)

add_executable(lzhw_info src/hw_info.cpp)
target_link_libraries(lzhw_info PRIVATE LevelZero::LevelZero)
target_compile_features(lzhw_info PRIVATE cxx_std_17)
