SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

add_executable(approxx-test
        main.cpp

        test_fw.cpp
        constant/test_constant_approximation.cpp
        linear/test_linear_approximation.cpp

	../source/logxx/logxx.cpp
        ../source/approxx/approximation.cpp
        ../source/approxx/constant/constant_approximation.cpp
        ../source/approxx/linear/linear_approximation.cpp
)
