#include "numeric_approximation.h"
#include <limits>
#include <cmath>

namespace approxx {
        double RoughOptimization(const std::function<double(double)>& testFunction, double minValue, double maxValue, double &optimalValue,
                unsigned int divisions)
        {
                double step = (maxValue - minValue) / static_cast<double>(divisions - 1);
                double minError = std::numeric_limits<double>::max();
                for (unsigned int i = 0; i < divisions; ++i){
                        double x = minValue + step * i;
                        double error = testFunction(x);
                        if (error < minError){
                                minError = error;
                                optimalValue = x;
                        }
                }
                return minError;
        }
        
        double OptimizeByDivisions(const std::function<double(double)>& testFunction, double initialValue, double initialStep, double &optimalValue,
                unsigned int maxDivisions, double minDifference)
        {
                double step = initialStep;
                static const double stepDivision = 0.5;
                
                double x = initialValue;
                unsigned int divisions(0);
                double prevY = testFunction(x);
                while (divisions < maxDivisions){
                        x += step;
                        double newY = testFunction(x);
                        if (std::fabs(newY - prevY) < minDifference){
                                break ;
                        } else if (newY > prevY){
                                step *= -stepDivision;
                                ++divisions;
                        }
                        prevY = newY;
                }
                optimalValue = x;
                return prevY;
        }
        
} //namespace approxx
