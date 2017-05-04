#==--- Xpress/CMakeLists.txt ------------------------------------------------==#

cmake_minimum_required(VERSION 3.4)
project(Xpress)

#==--- Versioning -----------------------------------------------------------==#

set(Xpress_VERSION 0.1.0)

#==--- Build Type -----------------------------------------------------------==#

option(GENERATE_SYSTEM_INFO "Can generate system info" TRUE)
if(NOT CMAKE_BUILD_TYPE) 
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type not specified!" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Check if the install prefix has Voxel appended, and if not, then add it:
string(REGEX MATCH ".*Voxel?" PREFIX_MATCH "${CMAKE_INSTALL_PREFIX}")
if ("${PREFIX_MATCH}" STREQUAL "")
  set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/Voxel" CACHE STRING
      "Install prefix" FORCE)
endif()

#==--- Options --------------------------------------------------------------==#

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Xpress_SOURCE_DIR}/cmake)
#include(VoxelSystemInfo)

#==--- Packages -------------------------------------------------------------==#

find_package(Voxel REQUIRED)

#==--- Compiler Flags -------------------------------------------------------==#

if(WIN32)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
  set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /O2"  )
else()
  set(FLAGS        "-std=c++1z -O3"                                     )
  set(DEBUG_FLAGS  "${FLAGS} -Wall -Wextra -Wpedantic ${CXX_CUDA_FLAGS}")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${FLAGS}"     )
  set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} ${DEBUG_FLAGS}" )
endif()

#==--- Set CXXFLAGS ---------------------------------------------------------==#

if(CMAKE_BUILD_TYPE MATCHES Release)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}"
      CACHE STRING "CXX FLAGS" FORCE)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "CXX FLAGS" FORCE)
endif()

#==--- Header install -------------------------------------------------------==#

install(DIRECTORY   ${Xpress_SOURCE_DIR}/include/Voxel/Xpress
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/Voxel/)

#==--- Subdirectories -------------------------------------------------------==#

add_subdirectory(docs)
add_subdirectory(tests)

#==--- Install --------------------------------------------------------------==#

# _Note__: We install Xpress as a component of Voxel, so that other CMake
#          applications can do Voxx::Xpress to use it.

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/Voxel/XpressConfigVersion.cmake"
  VERSION       ${Xpress_VERSION}
  COMPATIBILITY AnyNewerVersion)

#export(EXPORT    XpressTargets
#       FILE      "${CMAKE_CURRENT_BINARY_DIR}/Voxel/XpressTargets.cmake"
#       NAMESPACE Voxx::)
#export(EXPORT    XpressLibs
#       FILE      "${CMAKE_CURRENT_BINARY_DIR}/Voxel/XpressLibs.cmake"
#       NAMESPACE Voxx::)

configure_file(cmake/XpressConfig.cmake
               "${CMAKE_CURRENT_BINARY_DIR}/Voxel/XpressConfig.cmake"
               COPYONLY)

# This is relative to CMAKE_INSTALL_PREFIX:
#set(ConfigPackageLocation lib/cmake/Voxel)
#install(EXPORT      XpressTargets
#        FILE        XpressTargets.cmake
#        NAMESPACE   Voxx::
#        DESTINATION ${ConfigPackageLocation})
#install(EXPORT      XpressLibs
#        FILE        XpressLibs.cmake
#        NAMESPACE   Voxx::
#        DESTINATION ${ConfigPackageLocation})

set(ConfigPackageLocation lib/cmake/Voxel)
# This also installs relative to CMAKE_INSTALL_PREFIX:
install(
  FILES       cmake/XpressConfig.cmake
              "${CMAKE_CURRENT_BINARY_DIR}/Voxel/XpressConfigVersion.cmake"
  DESTINATION ${ConfigPackageLocation})

#==--- Print Configuration --------------------------------------------------==#

message(
"\n|==---------------------------------------------------------------------==|")
message(
  "| Configuration:                                                          |")
message(
  "|==---------------------------------------------------------------------==|")
message("| Xpress VERSION          : ${Xpress_VERSION}"                        )
message("| BUILD TYPE              : ${CMAKE_BUILD_TYPE}"                      )
message("| CMAKE_CXX_FLAGS_RELEASE : ${CMAKE_CXX_FLAGS_RELEASE}"               )
message("| CMAKE_CXX_FLAGS_DEBUG   : ${CMAKE_CXX_FLAGS_DEBUG}"                 )
message("| CMAKE_CXX_FLAGS         : ${CMAKE_CXX_FLAGS}"                       )
message("| INSTALL_PREFIX          : ${CMAKE_INSTALL_PREFIX}"                  )
message("| VOXEL FOUND             : ${VOXEL_FOUND}"                           )
message("| CUDA SUPPORTED          : ${CUDA_FOUND}"                            )
message("| CUDA ROOT               : ${CUDA_TOOLKIT_ROOT_DIR}"                 )
message("| PHYSICAL CORES          : ${VOXX_PHYSICAL_CORES}"                   )
message("| LOGICAL CORES           : ${VOXX_LOGICAL_CORES}"                    )
message("| CACHELINE SIZE          : ${VOXX_CACHELINE_SIZE}"                   )
message("| CPU INTRINSICS          : ${VOXX_INTRINSICS}"                       )
message(
"|==---------------------------------------------------------------------==|\n")
