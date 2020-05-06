SET(EXAMPLES
        plot_motor_ticks.cpp
        #print_motor_increments.cpp
        #plot_motor_increments.cpp
        #filter_motor_question.cpp
    )

foreach(SRC IN LISTS EXAMPLES)
    get_filename_component(TARGET ${SRC} NAME_WE)
    add_executable(${TARGET} ${SRC})
    target_link_libraries(${TARGET} utility)

endforeach()
