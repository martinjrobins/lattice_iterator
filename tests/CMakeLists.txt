add_executable(tests tests.cpp)
target_link_libraries(tests ${Lattice_LIBRARIES})
add_test(NAME tests COMMAND tests)
