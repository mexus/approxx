#ifndef APPROXIMATION_TCC
#define	APPROXIMATION_TCC

#include "approximation.h"

namespace approxx {

        template<class Key, class Value>
        bool Approximation::LoadData(const std::map<Key, Value> &sourceData){
                S_LOG("LoadData");
                bool init(false);
                double minKey(0.0), maxKey(0.0), minValue(0.0), maxValue(0.0);

                for (auto &pair : sourceData){
                        double key = static_cast<double>(pair.first);
                        double val = static_cast<double>(pair.second);

                        if (!init){
                                init = true;
                                minKey = key;
                                maxKey = key;
                                minValue = val;
                                maxValue = val;
                        } else {
                                if (key < minKey)
                                        minKey = key;
                                else if (key > maxKey)
                                        maxKey = key;
                                if (val < minValue)
                                        minValue = val;
                                else if (val > maxValue)
                                        maxValue = val;
                        }
                }

                static const double minDifference = 1E-5;
                if (Abs(maxKey - minKey) < minDifference){
                        log(logxx::error) << "Maximum and minimum keys should differ at least by " << minDifference << logxx::endl;
                        return false;
                } else {
                        keysConversion = GetConversion(minKey, maxKey);
                        valuesConversion = GetConversion(minValue, maxValue);
                        if (CheckConversion(keysConversion, "keys") && CheckConversion(valuesConversion, "values")){
                                for (auto &pair : sourceData){
                                        double key = static_cast<double>(pair.first);
                                        double val = static_cast<double>(pair.second);

                                        if (!InsertNormalized(NormalizeKey(key), NormalizeValue(val)))
                                                return false;
                                }
                                if (keys.size() != values.size())
                                        throw std::logic_error("Somehow it comes that keys.size() != values.size()");
                                return true;
                        } else
                                return false;
                }
        }
        
        
        template<class Function>
        double Approximation::CalculateAbsoluteError(Function f) const{
                double normDiff(0.0);
                size_t N = keys.size();
                for (size_t i = 0; i < N; ++i){
                        double x = keys[i];
                        double etalon = values[i];
                        double approximation = f(x);
                        
                        normDiff += Sqr(etalon - approximation);
                }
                return Sqrt(normDiff) / Abs(std::get<0>(valuesConversion));
        }
        
} // namespace approxx

#endif	/* APPROXIMATION_TCC */

