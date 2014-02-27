#include "linear_approximation.h"

namespace approxx {
        
        logxx::Log LinearApproximation::cLog("LinearApproximation");


        LinearApproximation::LinearApproximation() : Approximation() {
        }

        LinearApproximation::~LinearApproximation() {
        }
        
        double LinearApproximation::RelativeGet(double x) const {
                return coeffScale * x + coefShift;
        }

        double LinearApproximation::Approximate() {
                S_LOG("Approximate");
                coeffScale = 0.0;
                coefShift = 0.0;
                if (values.empty() || values.size() == 1){
                        log(logxx::error) << "There should be at least 2 values" << logxx::endl;
                        return 0.0;
                } else {
                        double alpha(0.0), beta(0.0), gamma(0.0), phi(0.0), psi(0.0);
                        size_t N = values.size();
                        gamma = N;
                        for (size_t i = 0; i < N; ++i){
                                alpha += Sqr(keys[i]);
                                beta += keys[i];
                                phi += values[i] * keys[i];
                                psi += values[i];
                        }
                        double determinant = alpha * gamma - Sqr(beta);
                        
                        coeffScale = (gamma * phi - beta * psi) / determinant;
                        coefShift = (-beta * phi + alpha * psi) / determinant;
                        
                        return CalculateRelativeError();
                }
        }


} //namespace approxx
