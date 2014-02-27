#ifndef TEST_EXPONENT_APPROXIMATION_H
#define	TEST_EXPONENT_APPROXIMATION_H

#include "../test_fw.h"
#include "../../source/approxx/numeric/exponent_approximation.h"

class TestExponentApproximation : public TestFW {
public:
        TestExponentApproximation();
        virtual ~TestExponentApproximation();
protected:
        virtual bool Tests();
        static logxx::Log cLog;
        
        static double rnd(double min, double max);
};

#endif	/* TEST_EXPONENT_APPROXIMATION_H */

