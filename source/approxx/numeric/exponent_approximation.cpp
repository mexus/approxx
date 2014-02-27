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
                double miminalError = std::numeric_limits<double>::max();
                double step = (to - from) / static_cast<double>(N - 1);
                for (size_t i = 0; i < N; ++i){
                        coeff = from + i * step ;
                        double error = CalculateRelativeError();
                        if (error < miminalError){
                                miminalError = error;
                                optimalCoeff = coeff;
                        }
                }
                return miminalError;
        }

        double ExponentApproximation::FindByDivisions(double step0) {
                double step = step0;
                static const double minDifference = 1E-5;
                static const unsigned int maxDivisions = 1000;
                static const double stepDivision = 0.5;
                
                unsigned int divisions(0);
                double prevY = CalculateRelativeError();
                while (divisions < maxDivisions){
                        coeff = coeff + step;
                        double newY = CalculateRelativeError();
                        if (fabs(newY - prevY) < minDifference){
                                break ;
                        } else if (newY > prevY){
                                step *= -stepDivision;
                                ++divisions;
                        }
                        prevY = newY;
                }
                return prevY;
        }

} // namespace approxx
