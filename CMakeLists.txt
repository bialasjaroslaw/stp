cmake_minimum_required(VERSION 3.14)

project(text_processing VERSION 0.2 LANGUAGES CXX)

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
    if(TEXT_PROCESSING_ENABLE_TESTS_SANITIZERS)
	if(MSVC)
	    target_compile_options(main PUBLIC -fsanitize=address)
	    target_link_options(main PUBLIC -fsanitize=address)
	else()
	    target_compile_options(main PUBLIC -fsanitize=address,leak,undefined)
	    target_link_options(main PUBLIC -fsanitize=address,leak,undefined)
	endif()
    endif()
    target_link_libraries(main PUBLIC text_processing gtest_main)
    gtest_discover_tests(main)
endif()
