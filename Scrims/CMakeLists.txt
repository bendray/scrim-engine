cmake_minimum_required(VERSION 3.1)
add_definitions(-DGAMELIBRARY_EXPORTS)
include_directories(../Engine/Include ${DEPENDENCIES_DIR}/nvidia/include)
set(SOURCE  dllmain.cpp
            Application.cpp
            BaseScrim.cpp
            Scrim.cpp 
            States/StateScene.cpp)
add_library(Scrims SHARED ${SOURCE})
target_link_libraries(Scrims ScrimEngine nv_math)
