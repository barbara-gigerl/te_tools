cmake_minimum_required(VERSION 3.0.0)
project(transfer_entropy VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

include_directories(include)

set(CMAKE_BUILD_TYPE Debug)

add_executable(transfer_entropy src/transfer_entropy.cpp src/binning.cpp src/test_data.cpp src/test_data_coupled.cpp src/test_data_network.cpp src/test_data_network_coupled.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
add_executable(transfer_entropy_test test/transfer_entropy_test.cpp src/transfer_entropy.cpp src/binning.cpp)
target_link_libraries(transfer_entropy_test ${GTEST_LIBRARIES} pthread)

add_executable(binning_test test/binning_test.cpp src/binning.cpp)
target_link_libraries(binning_test ${GTEST_LIBRARIES} pthread)

