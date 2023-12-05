cmake_minimum_required(VERSION 3.14)

# Add project_options v0.20.0
# https://github.com/cpp-best-practices/project_options
include(FetchContent)
FetchContent_Declare(_project_options URL https://github.com/aminya/project_options/archive/refs/tags/v0.20.0.zip)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

project(text_processing VERSION 0.2 LANGUAGES CXX)
option(DEVELOPER_BUILD "Enable developer mode" OFF)
option(TEXT_PROCESSING_ENABLE_TESTS "Enable test build" ON)

set(ENABLE_SANITIZER_ADDRESS "ENABLE_SANITIZER_ADDRESS")
if(MSVC)
    string(FIND "$ENV{PATH}" "$ENV{VSINSTALLDIR}" index_of_vs_install_dir)
    if(NOT "${index_of_vs_install_dir}" STREQUAL "-1")
        set(ENABLE_SANITIZER_ADDRESS "")
    endif()
endif()

if(DEVELOPER_BUILD)
    include(${_project_options_SOURCE_DIR}/src/DynamicProjectOptions.cmake)
    dynamic_project_options(
	ENABLE_CACHE
	ENABLE_CPPCHECK
	ENABLE_CLANG_TIDY
	${ENABLE_SANITIZER_ADDRESS}
	ENABLE_SANITIZER_LEAK
	ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
	ENABLE_COVERAGE
    )
endif()

add_library(text_processing INTERFACE)
target_sources(text_processing INTERFACE
    include/text_processing/common.hpp
    include/text_processing/count.hpp
    include/text_processing/find.hpp
    include/text_processing/join.hpp
    include/text_processing/remove.hpp
    include/text_processing/replace.hpp
    include/text_processing/split.hpp
    include/text_processing/sub.hpp
)
target_include_directories(text_processing INTERFACE include)

if (TEXT_PROCESSING_ENABLE_TESTS AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Compiler id is ${CMAKE_CXX_COMPILER_ID}")
    option(TEXT_PROCESSING_ENABLE_FUZZING "Build fuzzing tests" ON)
endif()

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
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    add_executable(main 
	common.cc
	count.cc
	find.cc
	join.cc 
	remove.cc 
	replace.cc 
	split.cc 
	sub.cc
    )

    target_link_libraries(main PRIVATE text_processing gtest_main)
    if(DEVELOPER_BUILD)
	target_link_libraries(main PRIVATE project_options project_warnings)
	if(TEXT_PROCESSING_ENABLE_FUZZING)
	    message(STATUS "Fuzzing enabled")
	    add_subdirectory(fuzzer)
	endif()
    endif()
    gtest_discover_tests(main)
    
endif()
