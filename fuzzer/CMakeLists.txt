add_executable(fuzz_tester fuzz_tester.cpp)
target_link_libraries(fuzz_tester
    PRIVATE 
	text_processing
	-coverage
	-fsanitize=fuzzer,undefined,address,leak
)
target_compile_options(fuzz_tester 
    PRIVATE 
	-fsanitize=fuzzer,undefined,address,leak
)

# Allow short runs during automated testing to see if something new breaks
set(FUZZ_RUNTIME
    10
    CACHE STRING "Number of seconds to run fuzz tests during ctest run") # Default of 10 seconds

add_test(NAME fuzz_tester_run COMMAND fuzz_tester -max_total_time=${FUZZ_RUNTIME})
