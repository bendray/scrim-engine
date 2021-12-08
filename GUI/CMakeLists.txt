cmake_minimum_required(VERSION 2.8)
add_definitions(-DGUILIBRARY_EXPORTS)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(../Engine/Include)
set(SOURCE  GUI.hpp
	    GUI.cpp
	    BitmapFont.hpp
	    BitmapFont.cpp
	    Button.hpp
	    Button.cpp
	    Edit.hpp
	    Edit.cpp
	    Label.hpp
	    Label.cpp
	    States/StateButton.hpp
	    States/StateButton.cpp
	    States/StateEdit.hpp
	    States/StateEdit.cpp
	    States/StateMain.hpp
	    States/StateMain.cpp)
add_library(GUI SHARED ${SOURCE})
target_link_libraries(GUI nv_math ScrimEngine)