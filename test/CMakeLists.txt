SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

add_executable(approxx-test
        main.cpp

        test_fw.cpp
        analytic/test_constant_approximation.cpp
        analytic/test_linear_approximation.cpp

	../source/logxx/logxx.cpp
        ../source/approxx/approximation.cpp
        ../source/approxx/analytic/constant_approximation.cpp
        ../source/approxx/analytic/linear_approximation.cpp
)
