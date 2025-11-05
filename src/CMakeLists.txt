set(aSRC arithmetic.cpp)  #new variable SRC, can add many files

include_directories(../include) # or include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_library(arithmetic STATIC ${aSRC})

