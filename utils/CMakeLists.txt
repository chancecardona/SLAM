find_package(Python2 COMPONENTS Development)

add_library(utils STATIC LegoRobot.cpp string_utility.cpp ../extern/matplotlib-cpp/matplotlibcpp.h)

target_include_directories(utils PUBLIC . PUBLIC ../extern/matplotlib-cpp)
target_link_libraries(utils Python2::Python)
