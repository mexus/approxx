#include "test_constant_approximation.h"
#include <cmath>

logxx::Log TestConstantApproximation::cLog("TestConstantApproximation");


TestConstantApproximation::TestConstantApproximation() : TestFW("constant")
{
}

TestConstantApproximation::~TestConstantApproximation() {
}

bool TestConstantApproximation::Tests() {
        return 
                Test(
                "Constant", std::map<double, double>{
                        {0.0, 10.0},
                        {1.0, 10.0},
                        {2.0, 10.0},
                        {3.0, 10.0},
                        {4.0, 10.0},
        }, 10.0, 0.0) &&
                Test(
                "Zero constant", std::map<double, double>{
                        {0.0, 0.0},
                        {1.0, 0.0},
                        {2.0, 0.0},
                        {3.0, 0.0},
        }, 0.0, 0.0) &&
                Test(
                "Linear", std::map<double, double>{
                        {1.0, 1.0},
                        {2.0, 2.0},
                        {3.0, 3.0}
        }, 2.0, 1.415);
}

bool TestConstantApproximation::Test(const std::string& label, const std::map<double, double>& set, double mean, double maxError) {
        D_LOG("Test");
        log(logxx::notice, label) << "Start test" << logxx::endl;
        BasicApproximation approx;
        bool res = Load(approx, set) && TestValues(approx, set) && TestResult(approx, mean, maxError);
        
        auto &s = log(logxx::notice, label);
        if (res)
                s << "Ok";
        else
                s << "Failed";
        s << logxx::endl;
        
        return res;
}

bool TestConstantApproximation::Load(BasicApproximation& approx, const std::map<double, double>& set) {
        S_LOG("Load");
        try {
                if (approx.LoadData(set))
                        return true;
                else {
                        log(logxx::error) << "Can't load data" << logxx::endl;
                        return false;
                }
        } catch (const std::exception& e){
                log(logxx::error) << "Catched an exception: " << e.what() << logxx::endl;
                return false;
        }
}

bool TestConstantApproximation::TestValues(const BasicApproximation& approx, const std::map<double, double>& set) {
        S_LOG("TestValues");
        size_t cnt(0);
        for (auto &pair: set){
                double exact = pair.second;
                double stored = approx.Get(cnt++);
                if (!Cmp(stored, exact)){
                        log(logxx::error) << "Wrong stored value: " << stored << ", should be " << exact << logxx::endl;
                        return false;
                }
        }
        return true;
}

bool TestConstantApproximation::TestResult(BasicApproximation& approx, double mean, double maxError)
{       
        S_LOG("TestResult");
        double approxError = approx.Approximate();
        double approximated = approx.Get(0.5);
        if (!Cmp(approximated, mean)){
                log(logxx::error) << "Wrong approximated value: " << approximated << ", should be " << mean << logxx::endl;
                return false;
        } else if (approxError > maxError){
                log(logxx::error) << "Too large approximation error: " << approxError << " should be at most " <<
                        maxError << logxx::endl;
                return false;
        } else {
                log(logxx::notice) << "Approximated value: " << approximated << ", approximation error: "
                        << approxError << logxx::endl;
                return true;
        }
}

bool TestConstantApproximation::Cmp(double x, double y) {
        return BasicApproximation::Cmp(x, y);
}
