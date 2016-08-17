cmake_minimum_required(VERSION 3.6)
project(SuffixTree)

include_directories(/opt/local/include)
link_directories(/opt/local/lib)

set(CMAKE_CXX_COMPILER /opt/local/libexec/ccache/clang++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++ -m64 -g")

file(GLOB_RECURSE SOURCE_FILES *.cpp *.hpp)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

find_package(Boost 1.59.0 COMPONENTS date_time filesystem system thread serialization REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIR})

set(LIBS ${LIBS} ${OpenCV_LIBS} ${Boost_LIBRARIES})

add_executable(SuffixTree ${SOURCE_FILES})

target_link_libraries(SuffixTree ${LIBS})
