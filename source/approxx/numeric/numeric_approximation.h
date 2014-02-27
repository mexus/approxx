#ifndef NUMERIC_APPROXIMATION_H
#define	NUMERIC_APPROXIMATION_H
#include <functional>

namespace approxx {
        double RoughOptimization(const std::function<double(double)>& testFunction, double minValue, double maxValue, double &optimalValue,
                unsigned int divisions = 10);
        double OptimizeByDivisions(const std::function<double(double)>& testFunction, double initialValue, double initialStep, double &optimalValue,
                unsigned int maxDivisions = 10, double minDifference = 1E-5);
} // namespace approx
#endif	/* NUMERIC_APPROXIMATION_H */
