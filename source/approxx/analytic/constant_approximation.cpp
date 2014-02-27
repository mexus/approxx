#include "constant_approximation.h"

namespace approxx {
        
        logxx::Log ConstantApproximation::cLog("ConstantApproximation");


        ConstantApproximation::ConstantApproximation() : Approximation() {
        }

        ConstantApproximation::~ConstantApproximation() {
        }

        double ConstantApproximation::Approximate() {
                S_LOG("Approximate");
                meanValue = 0.0;
                if (values.empty()){
                        log(logxx::error) << "There should be at least 1 value" << logxx::endl;
                        return 0.0;
                } else {
                        double sizeInversed = 1.0 / static_cast<double>(values.size());
                        for (auto &v : values){
                                meanValue += v * sizeInversed;
                        }
                        
                        return CalculateRelativeError();
                }
        }

        double ConstantApproximation::RelativeGet(double) const {
                return meanValue;
        }

} // namespace approxx
