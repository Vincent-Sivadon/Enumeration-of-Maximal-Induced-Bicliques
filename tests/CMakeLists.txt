# Fichiers sources
file(GLOB SRCS
    "src/*.cpp"
	"*.cpp"
)

# Crée l'executable "tests"
add_executable(tests ${SRCS} graph_tests.cpp)
target_link_libraries(tests graphes SDL2)
target_compile_options(tests PUBLIC -std=c++17)
add_custom_command(TARGET tests POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --magenta
                    "============== TESTS BIEN GENERES -taper ctest pour les executer- ==============")