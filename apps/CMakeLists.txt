# ===== Apps  ===== #

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(GLOB SRCS "*.cpp")

# For every app
foreach(source_file ${SRCS})
  # file ( GLOB ... ) gives absolute paths, we then transform it in relative
  # paths for example :
  # "/home/vincents/Documents/Projet/Enumeration-of-Maximal-Induced-Bicliques/examples/src/areConnectedTests.cpp"
  # changed in : "app"
  string(REPLACE ".cpp" "" app_name ${source_file})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" app_name
                 ${app_name})
        

  # on créé l'executable
  add_executable(${app_name} ${source_file})

  # on link les librairies
  target_link_libraries(${app_name} Graph)
  target_include_directories(${app_name} PUBLIC ${CMAKE_SOURCE_DIR}/include)
  target_compile_options(${app_name} PUBLIC -std=c++17 -Ofast)

endforeach(source_file ${SRCS})
