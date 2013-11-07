project(tuple_utils)

cmake_minimum_required(VERSION 2.8)

set (Tuple_Utils_VERSION_MAJOR 0)
set (Tuple_Utils_VERSION_MINOR 0)
set (Tuple_Utils_VERSION_PATH 1)

if (CMAKE_CXX_FLAGS)
  set(CXXFLAGS_PROVIDED true)
  set(CMAKE_CXX_FLAGS_DEBUG          "")
  set(CMAKE_CXX_FLAGS_MINSIZEREL     "")
  set(CMAKE_CXX_FLAGS_RELEASE        "")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "")
else (CMAKE_CXX_FLAGS)
  set(CXXFLAGS_PROVIDED false)
  set(CMAKE_CXX_FLAGS                "-std=c++11 -Wextra -Wall -pedantic")
  set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")
  set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os")
  set(CMAKE_CXX_FLAGS_RELEASE        "-O3")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
endif (CMAKE_CXX_FLAGS)

#add_subdirectory(src)
add_subdirectory(tests)

install(DIRECTORY src/ DESTINATION include/tuple_utils FILES_MATCHING PATTERN "*.hpp")
