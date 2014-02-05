#ifndef TEST_CONSTANT_APPROXIMATION_H
#define	TEST_CONSTANT_APPROXIMATION_H

#include "../test_fw.h"
#include "../../source/approxx/approximation.h"

typedef approxx::ConstantApproximation BasicApproximation;

class TestConstantApproximation : public TestFW {
public:
        TestConstantApproximation();
        virtual ~TestConstantApproximation();
        
protected:
        virtual bool Tests();
        
        bool Load(BasicApproximation &, const std::map<double, double> & set);
        bool TestValues(const BasicApproximation &, const std::map<double, double> & set);
        bool TestResult(BasicApproximation &, double mean, double maxError);
        
        bool Test(const std::string& label, const std::map<double, double> & set, double mean, double maxError);
       
//        BasicApproximation approx;
        static logxx::Log cLog;

        static bool Cmp(double, double);

};

#endif	/* TEST_CONSTANT_APPROXIMATION_H */
