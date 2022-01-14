# ============================================= GENERATION DES TESTS POUR VERSION AVEC LISTE D'ADJACENCE =============================================

file( GLOB TEST_SRCS "lst/*.cpp" )

# pour chaque TEST
foreach( testsourcefile ${TEST_SRCS} )
    # file ( GLOB ... ) donne les path absolu, on le transform en relative path
    # exemple : 
    # "/home/vincents/Documents/Projet/Enumeration-of-Maximal-Induced-Bicliques/tests/src/areConnectedTests"
    # transformé en :
    # "areConnectedTests"
    string( REPLACE ".cpp" "" testname ${testsourcefile} )
    string( REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/lst/ "" testname ${testname} )

    # on créé l'executable
    add_executable( ${testname} ${testsourcefile} )

    # on link les librairies
    target_link_libraries( ${testname} graphes SDL2 )
    target_compile_options(${testname} PUBLIC -std=c++17)

    # on ajoute cet executable à la liste des tests
    add_test(${testname} ${testname})

endforeach( testsourcefile ${TEST_SRCS} )



# ============================================= GENERATION DES TESTS POUR VERSION AVEC MATRICE D'ADJACENCE =============================================

file( GLOB TEST_SRCS "mat/*.cpp" )

# pour chaque TEST
foreach( testsourcefile ${TEST_SRCS} )
    # file ( GLOB ... ) donne les path absolu, on le transform en relative path
    # exemple : 
    # "/home/vincents/Documents/Projet/Enumeration-of-Maximal-Induced-Bicliques/tests/src/areConnectedTests"
    # transformé en :
    # "areConnectedTests"
    string( REPLACE ".cpp" "" testname ${testsourcefile} )
    string( REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/mat/ "" testname ${testname} )

    # on créé l'executable
    add_executable( ${testname} ${testsourcefile} )

    # on link les librairies
    target_link_libraries( ${testname} graphesMat SDL2 )
    target_compile_options(${testname} PUBLIC -std=c++17)

    # on ajoute cet executable à la liste des tests
    add_test(${testname} ${testname})

endforeach( testsourcefile ${TEST_SRCS} )