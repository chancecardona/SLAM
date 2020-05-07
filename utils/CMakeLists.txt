find_package(Python3 COMPONENTS Development)

add_library(utils STATIC 
	LegoRobot.cpp 
	string_utility.cpp 
	utility.h)

target_include_directories(utils 
	PUBLIC . ../extern/matplotlib-cpp
	PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(utils Python3::Python)
