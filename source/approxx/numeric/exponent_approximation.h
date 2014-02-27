#ifndef EXPONENT_APPROXIMATION_H
#define	EXPONENT_APPROXIMATION_H

#include "../approximation.h"

namespace approxx {

        class ExponentApproximation : public Approximation {
        public:
                ExponentApproximation();
                virtual ~ExponentApproximation();

                virtual double Approximate();
                
        protected:
                virtual double RelativeGet(double) const;
                
                static double Exponent(double x, double a);
                
                enum Mode {
                        straight,
                        inverse
                } currentMode;
                
                static logxx::Log cLog;
                double coeff = 0.0;
                
                double FindRoughCoefficient(double& optimalCoeff, size_t N, double from = -500.0, double to = 500.0);
                //double FindByDivisions(double from, double to);
                double FindByDivisions(double step0);

        };

}

#endif	/* EXPONENT_APPROXIMATION_H */

