#include <math.h>

#include "test_exponent_approximation.h"

logxx::Log TestExponentApproximation::cLog("TestExponentApproximation");
using namespace approxx;

TestExponentApproximation::TestExponentApproximation() : TestFW("exponent", logxx::notice) {
}

TestExponentApproximation::~TestExponentApproximation() {
}

bool TestExponentApproximation::Tests() {
        S_LOG("Tests");
        ExponentApproximation approxx;
        srand(time(nullptr));
        static const unsigned int tests = 5;
        static const unsigned int points = 20;
        for (unsigned int i = 0; i < tests; ++i){
                double a = rnd(0.0, 0.5);
                double b = rnd(0.0, 10.0);
                double c = rnd(-1E2, 1E2);
                log(logxx::notice) << "Testing f(x) = " << a << "exp(" << b << "x) + " << c << logxx::endl;
                
                std::map<double, double> vals;
                for (unsigned int point = 0; point < points; ++point){
                        double x = point * 1E-1;
                        vals[x] = a * exp(b * x) + c;
                }
                approxx.LoadData(vals);
                double error = approxx.Approximate();
                log(logxx::notice) << "Error: " << error << logxx::endl;
                approxx.ClearData();
        }
        return true;
}

double TestExponentApproximation::rnd(double min, double max) {
        return min + static_cast<double>(rand()) / (RAND_MAX + 1.0) * (max - min);
}

