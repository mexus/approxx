#include "approximation.h"
#include <cmath>
#include <algorithm>

namespace approxx {

        logxx::Log Approximation::cLog("Approximation");

        Approximation::Approximation(double minKeyInterval) : minKeyInterval(minKeyInterval) {
        }

        Approximation::~Approximation() {
        }

        void Approximation::ClearData() {
                keys.clear();
                values.clear();
        }

        double Approximation::Cmp(double a, double b) {
                static const double threshold = 1E-5;
                return std::abs(a - b) < threshold;
        }

        std::tuple<double, double> Approximation::GetConversion(double min, double max) {
                if (Cmp(min, max)){
                        if (Cmp(max, 0.0))
                                return std::make_tuple(1.0, 1.0);
                        else
                                return std::make_tuple(1.0 / max, 0.0);
                } else {
                        double frac = 1.0 / (max - min);
                        return std::make_tuple(frac, -min * frac);
                }
        }

        double Approximation::Normalize(double x, const std::tuple<double, double>& conversion) {
                return std::get<0>(conversion) * x + std::get<1>(conversion);
        }

        double Approximation::Denormalize(double x, const std::tuple<double, double>& conversion) {
                return (x - std::get<1>(conversion)) / std::get<0>(conversion); 
        }

        double Approximation::NormalizeKey(double key) const {
                return Normalize(key, keysConversion);
        }

        double Approximation::NormalizeValue(double value) const {
                return Normalize(value, valuesConversion);
        }

        double Approximation::DenormalizeKey(double key) const {
                return Denormalize(key, keysConversion);
        }

        double Approximation::DenoramlizeValue(double value) const {
                return Denormalize(value, valuesConversion);
        }

        double Approximation::Abs(double v) {
                return std::abs(v);
        }
        
        double Approximation::Sqr(double v){
                //return std::pow(v, 2);
                return v * v;
        }

        double Approximation::Sqrt(double v) {
                return std::sqrt(v);
        }

        bool Approximation::CheckConversion(const std::tuple<double, double>& conversion, const std::string& label) {
                S_LOG("CheckConversion");
                static const double minMultiplier = 1E-10;
                double c0 = std::abs(std::get<0>(conversion));
                if (c0 < minMultiplier){
                        log(logxx::error) << "Conversion multiplier for " << label << " should be at least " << minMultiplier << 
                                " by an absolute value, got " << c0 << logxx::endl;
                        return false;
                } else
                        return true;
        }
        
        bool Approximation::CheckKeyInterval(std::vector<double>::iterator firstGreater, double key) const {
                if (keys.empty())
                        return true;
                else {
                        bool checkCurrent = firstGreater != keys.end();
                        bool checkPrevious = firstGreater != keys.begin();

                        bool res(true);
                        if (checkCurrent)
                                res &= std::abs(*firstGreater - key) > minKeyInterval;
                        if (checkPrevious)
                                res &= std::abs(*(--firstGreater) - key) > minKeyInterval;
                        return res;
                }
        }

        bool Approximation::InsertNormalized(double key, double value) {
                S_LOG("InsertNormalized");
                auto firstGreater = std::find_if(keys.begin(), keys.end(), [&key](double k)->bool{
                        return k > key;
                });
                if (CheckKeyInterval(firstGreater, key)){
                        if (firstGreater == keys.end()){
                                keys.push_back(key);
                                values.push_back(value);
                        } else {
                                size_t N = firstGreater - keys.begin();
                                keys.insert(firstGreater, key);
                                values.insert(values.begin() + N, value);
                        }
                        return true;
                } else {
                        log(logxx::error) << "Interval between keys should be at least " << minKeyInterval << logxx::endl;
                        return false;
                }
        }

        double Approximation::Get(size_t n) const {
                return DenoramlizeValue(values[n]);
        }
        
        double Approximation::Get(double x) const {
                return DenoramlizeValue(RelativeGet(NormalizeKey(x)));
        }

        bool Approximation::IsEmpty() const {
                return keys.empty();
        }

        size_t Approximation::Size() const {
                return keys.size();
        }

        double Approximation::CalculateRelativeError(const std::function<double(double)>& f) const {
                const std::function<double(double)> function = f ? f : [this](double x){return RelativeGet(x);};
                double normDiff(0.0);
                size_t N = keys.size();
                for (size_t i = 0; i < N; ++i){
                        double x = keys[i];
                        double etalon = values[i];
                        double approximation = function(x);
                        
                        normDiff += Sqr(etalon - approximation);
                }
                return Sqrt(normDiff);
        }
        
        void Approximation::PrintData() const {
                S_LOG("PrintData");
                auto &s = log(logxx::info) << "\n";
                size_t N = keys.size();
                for (size_t i = 0; i < N; ++i){
                        double x = keys[i];
                        double y = values[i];
                        s << x << " " << y << "\n";
                }
                s << logxx::endl;
        }


} //namespace approxx
        