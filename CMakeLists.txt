cmake_minimum_required(VERSION 3.28)

project(words
  LANGUAGES CXX
  VERSION 0.1.0
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -Wc++11-extensions -fsanitize=undefined -g")

# List sources (all .cpp files in ./)
file(GLOB SOURCES *.cpp)

#add includes (all .h files in ./)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create executable
add_executable(words ${SOURCES})

