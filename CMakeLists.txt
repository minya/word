cmake_minimum_required(VERSION 3.28)

project(words
  LANGUAGES CXX
  VERSION 0.1.0
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -Wc++11-extensions -fsanitize=undefined -g")

# List sources (all .cpp files in ./)
file(GLOB SOURCES_CONVERTER src/utils/dict_converter/*.cpp)
file(GLOB SOURCES_WORDS src/words/*.cpp)
file(GLOB SOURCES_TESTS src/tests/*.cpp)
file(GLOB SOURCES_COMMON src/common/*.cpp)

set(CMAKE_BUILD_TYPE Debug)


#add includes (all .h files in ./)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Make 3 executables. One for the main program, one for the dictionary converter and one for the test suite.
add_executable(words ${SOURCES_WORDS} ${SOURCES_COMMON})
add_executable(dict_converter ${SOURCES_CONVERTER} ${SOURCES_COMMON})
add_executable(test_suite ${SOURCES_TESTS} ${SOURCES_COMMON})


