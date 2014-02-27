#include "exponent_approximation.h"
#include "numeric_approximation.h"
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
                        return Exponent(1.0 - x, coeff);
                else
                        throw std::logic_error("Unknown mode: " + std::to_string(currentMode));
        }

        double ExponentApproximation::Approximate() {
                S_LOG("Approximate");
                coeff = 0.0;
                currentMode = straight;
                if (values.size() >= 2){
                        
                        size_t roughN = 1E4;
                        
                        currentMode = straight;
                        double straightCoeff(0.0);
                        double straightError = FindRoughCoefficient(straightCoeff, roughN);
                        
                        currentMode = inverse;
                        double inverseCoeff(0.0);
                        double inverseError = FindRoughCoefficient(inverseCoeff, roughN);
                        
                        currentMode = (straightError < inverseError) ? straight : inverse;
                        coeff = (straightError < inverseError) ? straightCoeff : inverseCoeff;
                        
                        return FindByDivisions(1.0 / roughN);
                } else {
                        log(logxx::warning) << "There should be at least two values" << logxx::endl;
                        return 0.0;
                }
        }

        double ExponentApproximation::FindRoughCoefficient(double& optimalCoeff, size_t N, double from, double to) {
                auto testFunction = [this](double x)->double{
                        coeff = x;
                        return CalculateRelativeError();
                };
                return RoughOptimization(testFunction, from, to, optimalCoeff, N);
        }

        double ExponentApproximation::FindByDivisions(double step0) {
                auto testFunction = [this](double x)->double{
                        coeff = x;
                        return CalculateRelativeError();
                };
                double optimal(0.0);
                double error = OptimizeByDivisions(testFunction, coeff, step0, optimal);
                coeff = optimal;
                return error;
        }

} // namespace approxx
