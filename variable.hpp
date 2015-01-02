#ifndef VARIABLE_HPP_KJS
#define VARIABLE_HPP_KJS

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

template<class C=long double>
class Variable {
public:
    typedef unsigned long long int int_t;
    typedef long double float_t;
    Variable() : samples(0), sum(0), sum2(0) {}
    void Reset()
    {
        samples = 0;
        sum = 0;
        sum2 = 0;
    }
    void Add(const C val)
    {
        if (samples == std::numeric_limits<int_t>::max()) throw std::runtime_error("accumulator error: integer overflow");
        ++samples;
        sum = (sum * (samples - 1) + val) / static_cast<float_t>(samples);
        sum2 = (sum2 * (samples - 1) + val * val) / static_cast<float_t>(samples);
    }
    float_t Mean() const { return sum; }
    float_t Error() const
    {
        if (samples > 1) return sqrt(sum2 - sum * sum) / sqrt(samples);
        else return 0;
    }
    float_t Std() const
    {
        if (samples > 1) return sqrt(sum2 - sum * sum);
        else return 0;
    }
    int_t Samples() const { return samples; }
private:
    int_t samples;
    C sum;
    float_t sum2;
};

# endif // #ifndef VARIABLE_HPP_KJS

