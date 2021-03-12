//
// Created by sam on 11/03/2021.
//

#include <algorithm>

#include <UnitTest++/UnitTest++.h>

#include <libalgebra/libalgebra.h>
#include <libalgebra/alg_types.h>


#include "../time_and_details.h"
#include "../rng.h"
#include "../helpers.h"

#include "generic_coefficient.h"
#include "generic_lie_increment.h"
#include "generic_path.h"

template <unsigned Width>
generic_path<Width> make_innovative_path()
{
    std::vector<generic_lie_increment<Width, std::int32_t> > tmp(Width);
    mt19937 rng;
    UNIFORM_INT_DIST<std::int32_t> dist(0, Width-1);

    std::vector<int> seen;
    seen.reserve(Width);

    for (size_t i=0; i < Width; ++i) {
        size_t key;
        while (std::find(seen.begin(), seen.end(), key = dist(rng)) != seen.end()) {}
        tmp[i][key] = generic_coefficient<int32_t>::rand(rng);
        seen.push_back(key);
    }

    return generic_path<Width>(tmp);
}

namespace {

#if __cplusplus >= 201103UL
    constexpr
#endif
    size_t binomial_coeff(size_t n, size_t k)
    {
        return (k > n) ? 0 :
               (k == 0 || k == n) ? 1 :
               binomial_coeff(n-1, k-1) + binomial_coeff(n-1, k);
    }

}


SUITE(innovative_path_5_tests) {

    struct Fixture
    {
        static const unsigned width = 5;
        static const unsigned depth = 5;
        generic_path<width> path;

        struct rational_field
        {
            typedef mpq_class S;
            typedef mpq_class Q;
        };

        typedef alg_types<Fixture::depth, Fixture::width, Rational> RALGT;

        struct rational_sparse_framework
        {
            typedef typename RALGT::TENSOR TENSOR;
            typedef typename RALGT::LIE LIE;
            typedef typename RALGT::MAPS MAPS;
        };

        struct rational_dense_framework
        {
            typedef typename RALGT::TENSOR TENSOR;
            typedef typename RALGT::LIE LIE;
            typedef typename RALGT::MAPS MAPS;
        };

        struct rational_hybrid_framework
        {
            typedef typename RALGT::TENSOR TENSOR;
            typedef typename RALGT::LIE LIE;
            typedef typename RALGT::MAPS MAPS;
        };


        struct double_field
        {
            typedef double S;
            typedef double Q;
        };

        typedef alg_types<Fixture::depth, Fixture::width, DPReal> DALGT;

        struct double_sparse_framework
        {
            typedef typename DALGT::TENSOR TENSOR;
            typedef typename DALGT::LIE LIE;
            typedef typename DALGT::MAPS MAPS;
        };

        struct double_dense_framework
        {
            typedef typename DALGT::TENSOR TENSOR;
            typedef typename DALGT::LIE LIE;
            typedef typename DALGT::MAPS MAPS;
        };

        struct double_hybrid_framework
        {
            typedef typename DALGT::TENSOR TENSOR;
            typedef typename DALGT::LIE LIE;
            typedef typename DALGT::MAPS MAPS;
        };


        struct float_field
        {
            typedef float S;
            typedef float Q;
        };

        typedef alg_types<Fixture::depth, Fixture::width, Rational> FALGT;

        struct float_sparse_framework
        {
            typedef typename FALGT::TENSOR TENSOR;
            typedef typename FALGT::LIE LIE;
            typedef typename FALGT::MAPS MAPS;
        };

        struct float_dense_framework
        {
            typedef typename FALGT::TENSOR TENSOR;
            typedef typename FALGT::LIE LIE;
            typedef typename FALGT::MAPS MAPS;
        };

        struct float_hybrid_framework
        {
            typedef typename FALGT::TENSOR TENSOR;
            typedef typename FALGT::LIE LIE;
            typedef typename FALGT::MAPS MAPS;
        };

        Fixture() : path(make_innovative_path<width>())
        {}

        size_t sig_support(unsigned increments=width)
        {
            return binomial_coeff(width + increments, depth);
        }
    };

#include "double_path_suite.ins"
#include "float_path_suite.ins"
#include "rational_path_suite.ins"
#include "accuracy_suite.ins"

}


SUITE(innovative_path_10_tests) {

struct Fixture
{
    static const unsigned width = 10;
    static const unsigned depth = 3;
    generic_path<width> path;

    struct rational_field
    {
        typedef mpq_class S;
        typedef mpq_class Q;
    };

    typedef alg_types<Fixture::depth, Fixture::width, Rational> RALGT;

    struct rational_sparse_framework
    {
        typedef typename RALGT::TENSOR TENSOR;
        typedef typename RALGT::LIE LIE;
        typedef typename RALGT::MAPS MAPS;
    };

    struct rational_dense_framework
    {
        typedef typename RALGT::TENSOR TENSOR;
        typedef typename RALGT::LIE LIE;
        typedef typename RALGT::MAPS MAPS;
    };

    struct rational_hybrid_framework
    {
        typedef typename RALGT::TENSOR TENSOR;
        typedef typename RALGT::LIE LIE;
        typedef typename RALGT::MAPS MAPS;
    };


    struct double_field
    {
        typedef double S;
        typedef double Q;
    };

    typedef alg_types<Fixture::depth, Fixture::width, DPReal> DALGT;

    struct double_sparse_framework
    {
        typedef typename DALGT::TENSOR TENSOR;
        typedef typename DALGT::LIE LIE;
        typedef typename DALGT::MAPS MAPS;
    };

    struct double_dense_framework
    {
        typedef typename DALGT::TENSOR TENSOR;
        typedef typename DALGT::LIE LIE;
        typedef typename DALGT::MAPS MAPS;
    };

    struct double_hybrid_framework
    {
        typedef typename DALGT::TENSOR TENSOR;
        typedef typename DALGT::LIE LIE;
        typedef typename DALGT::MAPS MAPS;
    };


    struct float_field
    {
        typedef float S;
        typedef float Q;
    };

    typedef alg_types<Fixture::depth, Fixture::width, Rational> FALGT;

    struct float_sparse_framework
    {
        typedef typename FALGT::TENSOR TENSOR;
        typedef typename FALGT::LIE LIE;
        typedef typename FALGT::MAPS MAPS;
    };

    struct float_dense_framework
    {
        typedef typename FALGT::TENSOR TENSOR;
        typedef typename FALGT::LIE LIE;
        typedef typename FALGT::MAPS MAPS;
    };

    struct float_hybrid_framework
    {
        typedef typename FALGT::TENSOR TENSOR;
        typedef typename FALGT::LIE LIE;
        typedef typename FALGT::MAPS MAPS;
    };

    Fixture() : path(make_innovative_path<width>())
    {}

    size_t sig_support(unsigned increments=width)
    {
        return binomial_coeff(depth + increments, depth);
    }

};

#include "double_path_suite.ins"
#include "float_path_suite.ins"
#include "rational_path_suite.ins"
#include "accuracy_suite.ins"

}

SUITE(innovative_path_15_tests) {

struct Fixture
{
    static const unsigned width = 15;
    static const unsigned depth = 2;
    generic_path<width> path;

    struct rational_field
    {
        typedef mpq_class S;
        typedef mpq_class Q;
    };

    typedef alg_types<Fixture::depth, Fixture::width, Rational> RALGT;

    struct rational_sparse_framework
    {
        typedef typename RALGT::TENSOR TENSOR;
        typedef typename RALGT::LIE LIE;
        typedef typename RALGT::MAPS MAPS;
    };

    struct rational_dense_framework
    {
        typedef typename RALGT::TENSOR TENSOR;
        typedef typename RALGT::LIE LIE;
        typedef typename RALGT::MAPS MAPS;
    };

    struct rational_hybrid_framework
    {
        typedef typename RALGT::TENSOR TENSOR;
        typedef typename RALGT::LIE LIE;
        typedef typename RALGT::MAPS MAPS;
    };


    struct double_field
    {
        typedef double S;
        typedef double Q;
    };

    typedef alg_types<Fixture::depth, Fixture::width, DPReal> DALGT;

    struct double_sparse_framework
    {
        typedef typename DALGT::TENSOR TENSOR;
        typedef typename DALGT::LIE LIE;
        typedef typename DALGT::MAPS MAPS;
    };

    struct double_dense_framework
    {
        typedef typename DALGT::TENSOR TENSOR;
        typedef typename DALGT::LIE LIE;
        typedef typename DALGT::MAPS MAPS;
    };

    struct double_hybrid_framework
    {
        typedef typename DALGT::TENSOR TENSOR;
        typedef typename DALGT::LIE LIE;
        typedef typename DALGT::MAPS MAPS;
    };


    struct float_field
    {
        typedef float S;
        typedef float Q;
    };

    typedef alg_types<Fixture::depth, Fixture::width, Rational> FALGT;

    struct float_sparse_framework
    {
        typedef typename FALGT::TENSOR TENSOR;
        typedef typename FALGT::LIE LIE;
        typedef typename FALGT::MAPS MAPS;
    };

    struct float_dense_framework
    {
        typedef typename FALGT::TENSOR TENSOR;
        typedef typename FALGT::LIE LIE;
        typedef typename FALGT::MAPS MAPS;
    };

    struct float_hybrid_framework
    {
        typedef typename FALGT::TENSOR TENSOR;
        typedef typename FALGT::LIE LIE;
        typedef typename FALGT::MAPS MAPS;
    };


    Fixture() : path(make_innovative_path<width>())
    {}

    size_t sig_support(unsigned increments=width)
    {
        return binomial_coeff(depth + increments, depth);
    }

};

#include "double_path_suite.ins"
#include "float_path_suite.ins"
#include "rational_path_suite.ins"
#include "accuracy_suite.ins"

}