cmake_minimum_required(VERSION 3.15)
project(SocialNetwork CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra)
endif()

enable_testing()

# The four components + loader. Add new .cpp files to a component HERE.
add_library(core STATIC
  src/LinkedList.cpp
  src/HashTable.cpp
  src/Graph.cpp
  src/Ranking.cpp
  src/Loader.cpp)
target_include_directories(core PUBLIC src)
target_compile_definitions(core PUBLIC DATA_DIR="${CMAKE_SOURCE_DIR}/data")

add_executable(social_app src/main.cpp)
target_link_libraries(social_app core)

foreach(t test_linkedlist test_hashtable test_graph test_ranking test_loader test_integration)
  add_executable(${t} tests/${t}.cpp)
  target_link_libraries(${t} core)
  add_test(NAME ${t} COMMAND ${t})
endforeach()

add_executable(bench_timing tests/bench_timing.cpp)
target_link_libraries(bench_timing core)

