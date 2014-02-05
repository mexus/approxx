#include <vector>
#include <map>

#include "../source/logxx/logxx.h"
logxx::Log log("main");

#include "constant/test_constant_approximation.h"
#include "linear/test_linear_approximation.h"


std::map<std::shared_ptr<TestFW>, bool> tests;

template<class T, class ...Args>
void AddTest(bool defaultVal, Args&& ...args){
        static_assert(std::is_base_of<TestFW, T>::value, "T should be derived from TestFW");
        tests[std::make_shared<T>(args...)] = defaultVal;
}

void SetAll(bool val){
        for (auto &pair : tests){
                pair.second = val;
        }
}

void Set(const std::string& arg){
        if (!arg.empty()){
                bool val;
                std::string label;
                if (arg[0] == '-'){
                        label = arg.substr(1);
                        val = false;
                } else{
                        label = arg;
                        val = true;
                }
                if (!label.empty()){
                        for (auto &pair : tests){
                                if (pair.first->GetLabel() == label){
                                        pair.second = val;
                                        return ;
                                }
                        }
                        log(logxx::warning) << "No test {" << label << "} found" << logxx::endl;
                }
        }
}

void PrintStrings(std::ostream& s, const std::vector<std::string> &v){
        auto n = v.size();
        for (decltype(n) i = 0; i < n; ++i){
                s << v[i];
                if (i != n - 1)
                        s << ", ";
        }
}

int main(int argc, char **argv) {
        logxx::GlobalLogLevel(logxx::warning);
        bool res(true);
        
        AddTest<TestConstantApproximation>(true);
        AddTest<TestLinearApproximation>(true);
        
        if (argc < 2)
                SetAll(true);
        else {
                for (int i = 1; i < argc; ++i){
                        std::string arg(argv[i]);
                        if (arg == "all")
                                SetAll(true);
                        else if (arg == "none")
                                SetAll(false);
                        else
                                Set(arg);
                }
        }
        
        log(logxx::info) << "Starting tests" << logxx::endl;
        
        std::vector<std::string> passed, failed;
        
        for (auto &pair : tests){
                if (pair.second){
                        std::string label = pair.first->GetLabel();
                        bool testRes = pair.first->RunTests();
                        if (testRes)
                                passed.push_back(label);
                        else
                                failed.push_back(label);
                        res &= testRes;
                }
        }
        
        if (!passed.empty()){
                auto &s = log(logxx::info) << "PASSED tests: ";
                PrintStrings(s, passed);
                s << logxx::endl;
        } else
                log(logxx::info) << "No tests passed" << logxx::endl;
        
        if (!failed.empty()){
                auto &s = log(logxx::info) << "FAILED tests: ";
                PrintStrings(s, failed);
                s << logxx::endl;
        } else
                log(logxx::info) << "No tests failed" << logxx::endl;
        
        return res ? 0 : 1;
}

