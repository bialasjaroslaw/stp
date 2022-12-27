cmake_minimum_required(VERSION 3.14)

# Add project_options v0.20.0
# https://github.com/cpp-best-practices/project_options
include(FetchContent)
FetchContent_Declare(_project_options URL https://github.com/aminya/project_options/archive/refs/tags/v0.20.0.zip)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

project(text_processing VERSION 0.2 LANGUAGES CXX)

project_options(
    ENABLE_CPPCHECK
    ENABLE_CLANG_TIDY
    ENABLE_SANITIZER_ADDRESS
    ENABLE_SANITIZER_LEAK
    ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
)

add_library(text_processing INTERFACE 
    include/text_processing/common.hpp
    include/text_processing/count.hpp
    include/text_processing/find.hpp
    include/text_processing/join.hpp
    include/text_processing/remove.hpp
    include/text_processing/replace.hpp
    include/text_processing/split.hpp
    include/text_processing/sub.hpp
)
target_include_directories(text_processing INTERFACE include/text_processing)
option(TEXT_PROCESSING_ENABLE_TESTS "Build tests using gtest" OFF)
option(TEXT_PROCESSING_ENABLE_TESTS_SANITIZERS "Build tests with sanitizers" ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif()

if(TEXT_PROCESSING_ENABLE_TESTS)
    include(FetchContent)
    include(CTest)
    include(GoogleTest)

    enable_testing()
    FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        58d77fa8070e8cec2dc1ed015d66b454c8d78850 # release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)
    add_executable(main 
	count.cc
	find.cc
	join.cc 
	remove.cc 
	replace.cc 
	split.cc 
	sub.cc
    )

    target_link_libraries(main PRIVATE text_processing gtest_main project_options project_warnings)
    gtest_discover_tests(main)
endif()
