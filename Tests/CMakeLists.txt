cmake_minimum_required(VERSION 3.1)
add_definitions(-DGTEST_ON)
add_definitions(-DGTEST_HAS_PTHREAD=1)
if(MSVC)
    set_property(TARGET gtest PROPERTY IMPORTED_LOCATION ${SDK_DIR}/Lib/gtest.lib)
else(MSVC)
    set_property(TARGET gtest PROPERTY IMPORTED_LOCATION ${SDK_DIR}/Lib/libgtest.a)
endif(MSVC)

set(SOURCE 
    ../ThirdParty/gmock/src/gmock-all.cc
    stubs.hpp
    main.cpp
    TestDelegates.cpp
    TestInput.cpp
    TestInterface.cpp
    TestStateMachine.cpp)
include_directories(
    ../ThirdParty/gtest/include
    ../ThirdParty/gmock/include
    ../ThirdParty/gmock
    ${DEPENDENCIES_DIR}/nvidia/include
    ../Engine/include
    ../Scrims
    )

link_directories(${SDK_DIR}/Lib)
add_executable(Test ${SOURCE})
target_link_libraries(Test gtest nv_math ScrimEngine)
add_custom_command(TARGET Test POST_BUILD
    COMMAND "$<TARGET_FILE:Test>")
