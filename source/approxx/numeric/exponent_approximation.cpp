#include "exponent_approximation.h"
#include <cmath>

namespace approxx{
        
        logxx::Log ExponentApproximation::cLog("ExponentApproximation");

        ExponentApproximation::ExponentApproximation() : Approximation() {
        }

        ExponentApproximation::~ExponentApproximation() {
        }
        
        double ExponentApproximation::Exponent(double x, double a) {
                static const double threshold = 1E-5;
                if (std::abs(a) < threshold)
                        return x;
                else
                        return (std::exp(a * x) - 1.0) / (std::exp(a) - 1.0);
        }
        
        double ExponentApproximation::RelativeGet(double x) const {
                if (currentMode == straight)
                        return Exponent(x, coeff);
                else if (currentMode == inverse)
                        return -Exponent(1.0 - x, -coeff);
                else
                        throw std::logic_error("Unknown mode: " + std::to_string(currentMode));
        }

        double ExponentApproximation::Approximate() {
                coeff = 0.0;
                currentMode = straight;
                if (values.empty()){
                        log(logxx::warning) << "There should be at least one value" << logxx::endl;
                        return 0.0;
                } else {
                        return 0.0;
                }
        }

} // namespace approxx
