#==--- cmake/VoxelConfig.cmake ----------------------------------------------==#
#
#                                 	 Voxel 
#
#                         Copyright (c) 2017 Rob Clucas
#  
#  This file is distributed under the MIT License. See LICENSE for details.
#
#==--------------------------------------------------------------------------==#
#
# Description : This file defines the cmake configuration file for voxel.
#           
#==--------------------------------------------------------------------------==#

get_filename_component(Xpress_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)

# Define the cmake installation directory:
#set(Voxel_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}")

# Provide all the library targets:
#include("${CMAKE_CURRENT_LIST_DIR}/XpressTargets.cmake")

#find_package(CUDA)
#if (CUDA_FOUND)
#  set(Voxel_CUDA_SUPPORT TRUE)
#  set(Voxel_DEFINITIONS  -DVoxxCudaSupported)
#endif()

# Define the include directories:
set(Xpress_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../../../include")
set(Xpress_LIBRARY_DIRS "${CMAKE_CURRENT_LIST_DIR}/../../../lib"    )
set(Xpress_LIBRARYS     																						)
set(Xpress_DEFINITIONS  "${Xpress_DEFINITIONS}" 										)

set(SupportedComponents )

set(Xpress_FOUND True)

# Check that all the components are found:
# And add the components to the Voxel_LIBS parameter:
foreach(comp ${Xpress_FIND_COMPONENTS})
	if (NOT ";${SupportedComponents};" MATCHES comp)
		set(Xpress_FOUND False)
		set(Xpress_NOT_FOUND_MESSAGE "Unsupported component: ${comp}")
	endif()
	set(Xpress_LIBS "${Xpress_LIBS} -l{comp}")
	if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${comp}Targets.cmake")
		include("${CMAKE_CURRENT_LIST_DIR}/${comp}Targets.cmake")
	endif()
endforeach()