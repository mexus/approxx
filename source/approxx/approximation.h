#ifndef APPROXIMATION_H
#define	APPROXIMATION_H
#include <map>
#include <vector>
#include <tuple>
#include <functional>

#include "../logxx/logxx.h"

namespace approxx {

        class Approximation {
        public:
                Approximation(double minKeyInterval = 1E-05);
                virtual ~Approximation();

                template<class Key, class Value>
                bool LoadData(const std::map<Key, Value> &);
                void ClearData();
                
                bool IsEmpty() const;
                size_t Size() const;
                double Get(size_t) const;
                double Get(double) const;
                
                virtual double Approximate() = 0;
                
                const double minKeyInterval;
                
                static double Cmp(double, double);
        protected:
                virtual double RelativeGet(double) const = 0;

                std::vector<double> keys, values;
                std::tuple<double, double> keysConversion, valuesConversion;

                static logxx::Log cLog;
                double NormalizeKey(double key) const;
                double NormalizeValue(double value) const;
                double DenormalizeKey(double key) const;
                double DenoramlizeValue(double value) const;
                
                static double Normalize(double, const std::tuple<double, double>& conversion);
                static double Denormalize(double, const std::tuple<double, double>& conversion);
                static double Abs(double);
                static double Sqr(double);
                static double Sqrt(double);
                
                double CalculateAbsoluteError(const std::function<double(double)>& = nullptr) const;
        private:

                bool CheckKeyInterval(std::vector<double>::iterator firstGreater, double key) const;
                bool InsertNormalized(double key, double value);

                static std::tuple<double, double> GetConversion(double min, double max);
                static bool CheckConversion(const std::tuple<double, double> &, const std::string & label);
        };
} // namespace approxx

#include "approximation.tcc"

#include "analytic/constant_approximation.h"
#include "analytic/linear_approximation.h"

#endif	/* APPROXIMATION_H */

