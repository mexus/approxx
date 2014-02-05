#include "test_linear_approximation.h"
#include <cstdlib>
#include <stdlib.h>

logxx::Log TestLinearApproximation::cLog("TestLinearApproximation");

TestLinearApproximation::TestLinearApproximation() : TestFW("Linear approximation") {
        std::srand(time(NULL));
}

TestLinearApproximation::~TestLinearApproximation() {
}

bool TestLinearApproximation::Tests() {
        static const int tests = 10000;
        return TestConstants(tests) && TestLinears(tests);
}

bool TestLinearApproximation::TestConstants(int tests) {
        S_LOG("TestConstants");
        log(logxx::info) << "Testing approximation of constants" << logxx::endl;
        for(int i = 0; i < tests; ++i){
                double a = Random();
                double b = Random();
                if (!Test(a, b)){
                        log(logxx::error) << "Failed while testing y = " << a << " * x + " << b << logxx::endl;
                        return false;
                }
        }
        return true;
}

bool TestLinearApproximation::TestLinears(int tests) {
        S_LOG("TestLinear");
        log(logxx::info) << "Testing approximation of linear functions" << logxx::endl;
        for(int i = 0; i < tests; ++i){
                double c = Random();
                if (!Test(c)){
                        log(logxx::error) << "Failed while testing y = " << c << logxx::endl;
                        return false;
                }
        }
        return true;
}

double TestLinearApproximation::Random() {
        static const double minValue = -1E7;
        static const double maxValue = 1E7;
        double normalized = static_cast<double>(std::rand()) / (RAND_MAX + 1.0);
        return minValue + normalized * (maxValue - minValue);
}

bool TestLinearApproximation::Cmp(double x, double y) {
        return approxx::Approximation::Cmp(x, y);
}

bool TestLinearApproximation::Test(double constant) {
        S_LOG("Test constant");
        approxx::LinearApproximation approximation;
        
        auto etalonFunction = [constant](double)->double{return constant;};
        
        if (!Fill(approximation, etalonFunction)){
                log(logxx::error) << "Can't load data for constant = " << constant << logxx::endl;
                return false;
        } else {
                double error = approximation.Approximate();
                double val = approximation.Get(0.0);
                if (!Cmp(error, 0.0)){
                        log(logxx::error) << "Error should be 0.0, but it is " << error << logxx::endl;
                        return false;
                } else {
                        if (!Check(approximation, etalonFunction)){
                                log(logxx::error) << "Value should be " << constant << ", but it is " << val << logxx::endl;
                                return false;
                        }
                        return true;
                }
        }
}

bool TestLinearApproximation::Test(double a, double b) {
        S_LOG("Test linear function");
        approxx::LinearApproximation approximation;
        
        auto etalonFunction = [a, b](double x)->double{return a * x + b;};
        
        if (!Fill(approximation, etalonFunction)){
                log(logxx::error) << "Can't load data for linear function = " << a << " * x + " << b << logxx::endl;
                return false;
        } else {
                double error = approximation.Approximate();
                if (!Cmp(error, 0.0)){
                        log(logxx::error) << "Error should be 0.0, but it is " << error << logxx::endl;
                        return false;
                } else if (!Check(approximation, etalonFunction)){
                                log(logxx::error) << "Comparison for linear function = " << a << " * x + " << b << logxx::endl;
                                return false;
                } else
                        return true;
        }
}
