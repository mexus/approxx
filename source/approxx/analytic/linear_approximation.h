#ifndef LINEAR_APPROXIMATION_H
#define	LINEAR_APPROXIMATION_H

#include "../approximation.h"

namespace approxx {

        class LinearApproximation : public Approximation {
        public:
                LinearApproximation();
                virtual ~LinearApproximation();
                
                virtual double Approximate();

        protected:
                static logxx::Log cLog;
                virtual double RelativeGet(double) const;

                double coeffScale = 0.0;
                double coefShift = 0.0;
        };
        
} // namespace approxx

#endif	/* LINEAR_APPROXIMATION_H */

