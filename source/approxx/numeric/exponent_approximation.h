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
                
                enum mode {
                        straight,
                        inverse
                } currentMode;
                
                static logxx::Log cLog;
                double coeff = 0.0;

        };

}

#endif	/* EXPONENT_APPROXIMATION_H */

