#ifndef TEST_LINEAR_APPROXIMATION_H
#define	TEST_LINEAR_APPROXIMATION_H

#include "../test_fw.h"
#include "../../source/approxx/approximation.h"

class TestLinearApproximation : public TestFW {
public:
        TestLinearApproximation();
        virtual ~TestLinearApproximation();
protected:
        static logxx::Log cLog;

        virtual bool Tests();
        
        bool TestConstants(int tests);
        bool TestLinears(int tests);
        
        bool Test(double constant);
        bool Test(double a, double b);
        double Random();
        
        template<class Function>
        static bool Fill(approxx::Approximation& a, Function f){
                std::map<double, double> set;
                for (double x = start; x <= end; x += step)
                        set[x] = f(x);
                return a.LoadData(set);
        }
        
        template<class Function>
        static bool Check(approxx::Approximation& a, Function f){
                S_LOG("Check");
                for (double x = start; x <= end; x += step){
                        double etalon = f(x);
                        double val = a.Get(x);
                        if (!approxx::Approximation::Cmp(etalon, val)){
                                log(logxx::error) << "At " << x << ": got value " << val << ", shoduld be " << etalon << logxx::endl;
                                return false;
                        }
                }
                return true;
        }
        
        static bool Cmp(double x, double y);
        
        static constexpr double start = -10.0;
        static constexpr double end = 10.0;
        static constexpr double step = 0.1;
};

#endif	/* TEST_LINEAR_APPROXIMATION_H */

