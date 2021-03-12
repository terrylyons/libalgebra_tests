//
// Created by sam on 11/03/2021.
//

#ifndef LIBALGEBRAUNITTESTS_GENERIC_COEFFICIENT_H
#define LIBALGEBRAUNITTESTS_GENERIC_COEFFICIENT_H

#if __cplusplus >= 201103UL
#define CONSTEXPR constexpr
#else
#define CONSTEXPR
#endif

#include "../rng.h"

template <typename Integer>
struct generic_coefficient
{
    Integer numerator, denominator;

    CONSTEXPR generic_coefficient() : numerator(0), denominator(1)
    {}

    CONSTEXPR generic_coefficient(Integer a, Integer b) : numerator(a), denominator(b)
    {}

    explicit CONSTEXPR generic_coefficient(Integer i) : numerator(i), denominator(1)
    {}

    explicit CONSTEXPR operator float() const
    {
        return float(numerator) / denominator;
    }

    explicit CONSTEXPR operator double() const
    {
        return double(numerator) / denominator;
    }

    template <typename Rational>
    explicit operator Rational() const
    {
        return Rational(numerator) / Rational(denominator);
    }

    template <typename RandomSource>
    static generic_coefficient rand(RandomSource& rng)
    {
        UNIFORM_INT_DIST<int32_t> distn(-5, 5);
        UNIFORM_INT_DIST<int32_t> distd(1, 60);
        return generic_coefficient(distn(rng), distd(rng));
    }

};



#endif //LIBALGEBRAUNITTESTS_GENERIC_COEFFICIENT_H
