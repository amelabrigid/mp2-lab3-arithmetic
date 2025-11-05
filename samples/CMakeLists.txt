set(MAIN main_arithmetic.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_executable(main ${MAIN})
target_link_libraries(main arithmetic) #прилинковали к main.ехе библиотеку arithmetic

