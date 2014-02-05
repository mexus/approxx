#ifndef CONSTANT_APPROXIMATION_H
#define	CONSTANT_APPROXIMATION_H

#include "../approximation.h"

namespace approxx {

        class ConstantApproximation : public Approximation {
        public:
                ConstantApproximation();
                virtual ~ConstantApproximation();
                virtual double Approximate();
                
        protected:
                virtual double RelativeGet(double) const;
                static logxx::Log cLog;
                
                double meanValue;

        };
        
} //namespace approxx
#endif	/* CONSTANT_APPROXIMATION_H */

