cmake_minimum_required(VERSION 3.1)
if(EXISTS ${SDK_DIR})
    #generated from top project
else(EXISTS ${SDK_DIR})
    set(SDK_DIR "../../../SDK" CACHE PATH "")
endif(EXISTS ${SDK_DIR})
if(EXISTS ${DEPENDENCIES_DIR})
    #generated from top project
else(EXISTS ${DEPENDENCIES_DIR})
    set(DEPENDENCIES_DIR "../../../Dependencies" CACHE PATH "")
endif(EXISTS ${DEPENDENCIES_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SDK_DIR}/Lib)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${SDK_DIR}/Lib)
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

include_directories(${DEPENDENCIES_DIR}/nvidia/include/nv_math)
set(SOURCE ${DEPENDENCIES_DIR}/nvidia/include/nv_math/nv_math.cpp)
add_library(nv_math STATIC ${SOURCE})
set_property(TARGET nv_math PROPERTY POSITION_INDEPENDENT_CODE ON)
set_target_properties(nv_math PROPERTIES
         ARCHIVE_OUTPUT_DIRECTORY ${SDK_DIR}/Lib)
