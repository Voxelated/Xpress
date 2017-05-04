#==--- tests/CMakeLists.txt -------------------------------------------------==#

find_package(GTest REQUIRED)
find_package(Voxel REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS}
                    ${Voxel_INCLUDE_DIRS}
                    ${Xpress_SOURCE_DIR}/include)

add_definitions(${Voxel_DEFINITIONS})
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Phyz_SOURCE_DIR}/cmake)

#==--- Unit Tests ----------------------------------------------------------==#

add_executable(ArrayTests ArrayTests.cpp)
target_link_libraries(ArrayTests ${GTEST_BOTH_LIBRARIES})