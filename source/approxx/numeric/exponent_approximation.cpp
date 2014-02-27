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
                S_LOG("Approximate");
                coeff = 0.0;
                currentMode = straight;
                if (values.size() >= 2){
                        
//                        auto &s = log(logxx::notice, "Pairs") << "{";
//                        size_t N0 = values.size();
//                        for (size_t i = 0; i < N0; ++i){
//                                s << "{" << keys[i] << ", " << values[i] << "}";
//                                if (i != N0 - 1)
//                                        s << ", ";
//                        }
//                        s << "}" << logxx::endl;;
                        
                        size_t roughN = 10;
                        
                        currentMode = straight;
                        double straightCoeff(0.0);
                        double straightError = FindRoughCoefficient(straightCoeff, roughN);
                        
                        currentMode = inverse;
                        double inverseCoeff(0.0);
                        double inverseError = FindRoughCoefficient(inverseCoeff, roughN);
                        
                        currentMode = (straightError < inverseError) ? straight : inverse;
                        coeff = (straightError < inverseError) ? straightCoeff : inverseCoeff;
                        
                        return FindByDivisions(coeff - 1.0 / roughN, coeff + 1.0 / roughN);
                } else {
                        log(logxx::warning) << "There should be at least two values" << logxx::endl;
                        return 0.0;
                }
        }

        double ExponentApproximation::FindRoughCoefficient(double& optimalCoeff, size_t N, double from, double to) {
                double miminalError = std::numeric_limits<double>::max();
                for (size_t i = 0; i < N; ++i){
                        coeff = from + static_cast<double>(i) / static_cast<double>(N - 1) * (to - from);
                        double error = CalculateAbsoluteError();
                        if (error < miminalError){
                                miminalError = error;
                                optimalCoeff = coeff;
                        }
                }
                return miminalError;
        }

        double ExponentApproximation::FindByDivisions(double startFrom, double startTo) {
                double from = startFrom;
                double to = startTo;
                double error(0.0);
                for (int i = 0; i < 10; ++i){
                        size_t N = 10;
                        double optimalCoef(0.0);
                        error = FindRoughCoefficient(optimalCoef, N, from, to);
                        from = optimalCoef - 1.0 / N;
                        to = optimalCoef + 1.0 / N;
                }
                return error;
        }

} // namespace approxx
