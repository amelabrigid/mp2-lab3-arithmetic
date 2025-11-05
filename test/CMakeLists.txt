#set(GLOB SRC_TESTS"*.cpp")  # в переменную SRC_TESTS записываем все файлы по маске
set(SRC_TESTS test_main.cpp test_stack.cpp test_arithmetic.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../gtest)

add_executable(test test_main.cpp test_stack.cpp test_arithmetic.cpp)
target_link_libraries(test arithmetic gtest) #прилинковали к test.ехе библиотеку arithmetic