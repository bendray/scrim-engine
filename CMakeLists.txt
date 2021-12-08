cmake_minimum_required(VERSION 3.1)
project(Launcher)
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "DEBUG")
set(SDK_DIR "" CACHE PATH "") #path to sdk root folder
set(DEPENDENCIES_DIR "" CACHE PATH "") #path to external dependecies folder
if(EXISTS ${SDK_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SDK_DIR}/Bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SDK_DIR}/Lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SDK_DIR}/Lib)

    foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
            string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${SDK_DIR}/Bin)
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${SDK_DIR}/Lib)
            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${SDK_DIR}/Lib)
    endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
endif(EXISTS ${SDK_DIR})

include_directories(Engine/Include GUI Scrims Middleware ${DEPENDENCIES_DIR}/nvidia/include)
link_directories(${SDK_DIR}/Lib ${SDK_DIR}/Bin)

add_library(nv_math STATIC IMPORTED)
if(MSVC)
set_property(TARGET nv_math PROPERTY IMPORTED_LOCATION  ${SDK_DIR}/Lib/nv_math.lib)
else(MSVC)
set_property(TARGET nv_math PROPERTY IMPORTED_LOCATION  ${SDK_DIR}/Lib/libnv_math.a)
endif(MSVC)

add_library(ScrimEngine SHARED IMPORTED)
if(MSVC)
set_property(TARGET ScrimEngine PROPERTY IMPORTED_IMPLIB  ${SDK_DIR}/Lib/ScrimEngine.lib)
else(MSVC)
    if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
        set_property(TARGET ScrimEngine PROPERTY IMPORTED_LOCATION ${SDK_DIR}/Lib/libScrimEngine.so)
    else(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
        set_property(TARGET ScrimEngine PROPERTY IMPORTED_IMPLIB  ${SDK_DIR}/Lib/libScrimEngine.dll.a)
    endif(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
endif(MSVC)

if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    set(SOURCE_EXE  Common/Launcher.cpp 
                    Linux/Launcher/RenderWindow.cpp 
                    Common/main.cpp )
    set(PLATFORM_LIB X11 dl GL GLU)
    message(STATUS "CMAKE_SYSTEM_NAME:         " ${CMAKE_SYSTEM_NAME})
elseif(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
    set(SOURCE_EXE  Common/Launcher.hpp
                    Common/Launcher.cpp
                    Common/main.cpp
                    Win/Launcher/RenderWindow.hpp
                    Win/Launcher/RenderWindow.cpp )
    set(PLATFORM_LIB OpenGL32 glu32)
    message(STATUS "CMAKE_SYSTEM_NAME:         " ${CMAKE_SYSTEM_NAME})
else(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    message(STATUS "CMAKE_SYSTEM_NAME:         " ${CMAKE_SYSTEM_NAME})
    message(SEND_ERROR "Not found sources for this platform. Exit...")
endif(${CMAKE_SYSTEM_NAME} STREQUAL Linux)

string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)
message(STATUS "CMAKE_BUILD_TYPE:         " ${build_type} )
if (${build_type} STREQUAL debug)
	add_definitions(-DDEBUG)
endif(${build_type} STREQUAL debug)

add_definitions(-DUNICODE -D_UNICODE)

if(NOT MSVS)
    add_definitions(-std=c++17)
else(NOT MSVS)
    set(CMAKE_CXX_STANDARD 17)
endif(NOT MSVS)


#add_subdirectory(Dependencies)
#add_subdirectory(Editor)
add_subdirectory(Engine)
#add_subdirectory(Middleware)
add_subdirectory(GUI)
add_subdirectory(Scrims)
add_subdirectory(ThirdParty)
#add_dependencies(Test gtest)
add_subdirectory(Tests)
add_executable(Launcher WIN32 ${SOURCE_EXE})
add_dependencies(Launcher Test)
target_link_libraries(Launcher GUI Scrims ScrimEngine ${PLATFORM_LIB})
if(MSVC)
    set_property(TARGET Program APPEND PROPERTY LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
    set_property(TARGET Program APPEND PROPERTY LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
    set_property(TARGET Program APPEND PROPERTY LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:WINDOWS")
    set_property(TARGET Program APPEND PROPERTY LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
endif(MSVC)
