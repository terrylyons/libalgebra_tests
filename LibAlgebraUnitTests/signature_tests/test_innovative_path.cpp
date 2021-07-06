//
// Created by sam on 11/03/2021.
//

#include <algorithm>
#include <vector>
#include <map>

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
generic_path<Width> make_innovative_path(unsigned length)
{
    std::vector<generic_lie_increment<Width, int32_t> > tmp;
    tmp.reserve(length);
    mt19937 rng;
    UNIFORM_INT_DIST<int32_t> dist(0, Width-1);

    UNIFORM_INT_DIST<int32_t> distn(-5, 5);
    UNIFORM_INT_DIST<int32_t> distd(1, 60);

    std::vector<size_t> seen;
    seen.reserve(length);

    size_t key = dist(rng);
    std::vector<generic_coefficient<int32_t> > incr_tmp;
    incr_tmp.reserve(Width);
    for (size_t i=0; i <Width; ++i) {
        if (i == key) {
            incr_tmp.push_back(generic_coefficient<int32_t>(distn(rng), distd(rng)));
        } else {
            incr_tmp.push_back(generic_coefficient<int32_t>(0, 1));
        }
    }
    tmp.push_back(generic_lie_increment<Width, int32_t>(incr_tmp));
    seen.push_back(key);

    for (size_t i=1; i < length; ++i) {
        while (std::find(seen.begin(), seen.end(), key) != seen.end()) {
            key = dist(rng);
        }
        incr_tmp.clear();
        incr_tmp.reserve(Width);
        for (size_t i=0; i <Width; ++i) {
            if (i == key) {
                incr_tmp.push_back(generic_coefficient<int32_t>(distn(rng), distd(rng)));
            } else {
                incr_tmp.push_back(generic_coefficient<int32_t>(0, 1));
            }
        }
        tmp.push_back(generic_lie_increment<Width, int32_t>(incr_tmp));;
        seen.push_back(key);
    }
    assert(tmp.size() == length);

    return generic_path<Width>(tmp);
}

namespace {

#if __cplusplus >= 201103UL
    constexpr
#endif
    inline size_t binomial_coeff(size_t n, size_t k)
    {
        return (k > n) ? 0 :
               (k == 0 || k == n) ? 1 :
               binomial_coeff(n-1, k-1) + binomial_coeff(n-1, k);
    }

}




template <unsigned Width, unsigned Depth>
struct GenericFixture
{
    static const unsigned width = Width;
    static const unsigned depth = Depth;
    generic_path<width> path;

    float expected_float_error;
    double expected_double_error;

    typedef typename alg_types<2, 2, Rational>::SCA Rat;

    typedef alg::coefficients::coefficient_field<Rat> rational_field;

    struct rational_sparse_framework
    {
        typedef typename rational_field::S S;
        typedef typename rational_field::Q Q;
        typedef alg::free_tensor_basis<width, depth> TBASIS;
        typedef alg::lie_basis<width, depth> LBASIS;

        typedef alg::vectors::sparse_vector<
                TBASIS,
                rational_field,
                std::map<typename TBASIS::KEY, S>
        > SPTENS;

        typedef alg::vectors::sparse_vector<
                LBASIS,
                rational_field,
                std::map<typename LBASIS::KEY, S>
        > SPLIE;

        typedef alg::free_tensor<S, Q, width, depth, SPTENS> TENSOR;
        typedef alg::lie<rational_field, width, depth, SPLIE> LIE;
        typedef alg::maps<S, Q, width, depth, TENSOR, LIE> MAPS;

    };

    struct rational_dense_framework
    {
        typedef typename rational_field::S S;
        typedef typename rational_field::Q Q;
        typedef alg::free_tensor_basis<S, Q, width, depth> TBASIS;
        typedef alg::lie_basis<S, Q, width, depth> LBASIS;

        typedef alg::vectors::dense_vector<
                TBASIS,
                alg::TrivialCoeffs<TBASIS>
        > DTENS;

        typedef alg::vectors::sparse_vector<
                LBASIS,
                alg::TrivialCoeffs<LBASIS>
        > DLIE;

        typedef alg::free_tensor<S, Q, width, depth, DTENS> TENSOR;
        typedef alg::lie<S, Q, width, depth, DLIE> LIE;
        typedef alg::maps<S, Q, width, depth, TENSOR, LIE> MAPS;
    };

    struct rational_hybrid_framework
    {
        typedef typename rational_field::S S;
        typedef typename rational_field::Q Q;
        typedef alg::free_tensor_basis<S, Q, width, depth> TBASIS;
        typedef alg::lie_basis<S, Q, width, depth> LBASIS;

        typedef alg::vectors::hybrid_vector<
                TBASIS,
                alg::TrivialCoeffs<TBASIS>,
                alg::vectors::policy::basic_resize_policy,
                std::vector<S>,
                std::map<typename TBASIS::KEY, S>
        > HTENS;

        typedef alg::vectors::hybrid_vector<
                LBASIS,
                alg::TrivialCoeffs<LBASIS>,
                alg::vectors::policy::basic_resize_policy,
                std::vector<S>,
                std::map<typename LBASIS::KEY, S>
        > HLIE;

        typedef alg::free_tensor<S, Q, width, depth, HTENS> TENSOR;
        typedef alg::lie<S, Q, width, depth, HLIE> LIE;
        typedef alg::maps<S, Q, width, depth, TENSOR, LIE> MAPS;
    };


    struct double_field
    {
        typedef double S;
        typedef double Q;
    };

    struct double_sparse_framework
    {
        typedef typename double_field::S S;
        typedef typename double_field::Q Q;
        typedef alg::free_tensor_basis<S, Q, width, depth> TBASIS;
        typedef alg::lie_basis<S, Q, width, depth> LBASIS;

        typedef alg::vectors::sparse_vector<
                TBASIS,
                alg::TrivialCoeffs<TBASIS>,
                std::map<typename TBASIS::KEY, S>
        > SPTENS;

        typedef alg::vectors::sparse_vector<
                LBASIS,
                alg::TrivialCoeffs<LBASIS>,
                std::map<typename LBASIS::KEY, S>
        > SPLIE;

        typedef alg::free_tensor<S, Q, width, depth, SPTENS> TENSOR;
        typedef alg::lie<S, Q, width, depth, SPLIE> LIE;
        typedef alg::maps<S, Q, width, depth, TENSOR, LIE> MAPS;
    };

    struct double_dense_framework
    {
        typedef typename double_field::S S;
        typedef typename double_field::Q Q;
        typedef alg::free_tensor_basis<S, Q, width, depth> TBASIS;
        typedef alg::lie_basis<S, Q, width, depth> LBASIS;

        typedef alg::vectors::dense_vector<
                TBASIS,
                alg::TrivialCoeffs<TBASIS>
        > DTENS;

        typedef alg::vectors::sparse_vector<
                LBASIS,
                alg::TrivialCoeffs<LBASIS>
        > DLIE;

        typedef alg::free_tensor<S, Q, width, depth, DTENS> TENSOR;
        typedef alg::lie<S, Q, width, depth, DLIE> LIE;
        typedef alg::maps<S, Q, width, depth, TENSOR, LIE> MAPS;
    };

    struct double_hybrid_framework
    {
        typedef typename double_field::S S;
        typedef typename double_field::Q Q;
        typedef alg::free_tensor_basis<S, Q, width, depth> TBASIS;
        typedef alg::lie_basis<S, Q, width, depth> LBASIS;

        typedef alg::vectors::hybrid_vector<
                TBASIS,
                alg::TrivialCoeffs<TBASIS>,
                alg::vectors::policy::basic_resize_policy,
                std::vector<S>,
                std::map<typename TBASIS::KEY, S>
        > HTENS;

        typedef alg::vectors::hybrid_vector<
                LBASIS,
                alg::TrivialCoeffs<LBASIS>,
                alg::vectors::policy::basic_resize_policy,
                std::vector<S>,
                std::map<typename LBASIS::KEY, S>
        > HLIE;

        typedef alg::free_tensor<S, Q, width, depth, HTENS> TENSOR;
        typedef alg::lie<S, Q, width, depth, HLIE> LIE;
        typedef alg::maps<S, Q, width, depth, TENSOR, LIE> MAPS;
    };


    struct float_field
    {
        typedef float S;
        typedef float Q;
    };

    struct float_sparse_framework
    {
        typedef typename float_field::S S;
        typedef typename float_field::Q Q;
        typedef alg::free_tensor_basis<S, Q, width, depth> TBASIS;
        typedef alg::lie_basis<S, Q, width, depth> LBASIS;

        typedef alg::vectors::sparse_vector<
                TBASIS,
                alg::TrivialCoeffs<TBASIS>,
                std::map<typename TBASIS::KEY, S>
        > SPTENS;

        typedef alg::vectors::sparse_vector<
                LBASIS,
                alg::TrivialCoeffs<LBASIS>,
                std::map<typename LBASIS::KEY, S>
        > SPLIE;

        typedef alg::free_tensor<S, Q, width, depth, SPTENS> TENSOR;
        typedef alg::lie<S, Q, width, depth, SPLIE> LIE;
        typedef alg::maps<S, Q, width, depth, TENSOR, LIE> MAPS;
    };

    struct float_dense_framework
    {
        typedef typename float_field::S S;
        typedef typename float_field::Q Q;
        typedef alg::free_tensor_basis<S, Q, width, depth> TBASIS;
        typedef alg::lie_basis<S, Q, width, depth> LBASIS;

        typedef alg::vectors::dense_vector<
                TBASIS,
                alg::TrivialCoeffs<TBASIS>
        > DTENS;

        typedef alg::vectors::sparse_vector<
                LBASIS,
                alg::TrivialCoeffs<LBASIS>
        > DLIE;

        typedef alg::free_tensor<S, Q, width, depth, DTENS> TENSOR;
        typedef alg::lie<S, Q, width, depth, DLIE> LIE;
        typedef alg::maps<S, Q, width, depth, TENSOR, LIE> MAPS;
    };

    struct float_hybrid_framework
    {
        typedef typename float_field::S S;
        typedef typename float_field::Q Q;
        typedef alg::free_tensor_basis<S, Q, width, depth> TBASIS;
        typedef alg::lie_basis<S, Q, width, depth> LBASIS;

        typedef alg::vectors::hybrid_vector<
                TBASIS,
                alg::TrivialCoeffs<TBASIS>,
                alg::vectors::policy::basic_resize_policy,
                std::vector<S>,
                std::map<typename TBASIS::KEY, S>
        > HTENS;

        typedef alg::vectors::hybrid_vector<
                LBASIS,
                alg::TrivialCoeffs<LBASIS>,
                alg::vectors::policy::basic_resize_policy,
                std::vector<S>,
                std::map<typename LBASIS::KEY, S>
        > HLIE;

        typedef alg::free_tensor<S, Q, width, depth, HTENS> TENSOR;
        typedef alg::lie<S, Q, width, depth, HLIE> LIE;
        typedef alg::maps<S, Q, width, depth, TENSOR, LIE> MAPS;
    };

    GenericFixture() : path(make_innovative_path<width>(width)),
                       expected_double_error(1.0e-14),
                       expected_float_error(1.0e-6f)
    {}

    size_t sig_support(unsigned increments=width)
    {
        return binomial_coeff(increments + depth, depth);
    }
};




SUITE(innovative_path_5_tests) {

typedef GenericFixture<5, 5> Fixture;

#include "double_path_suite.ins"
#include "float_path_suite.ins"
#include "rational_path_suite.ins"
#include "accuracy_suite.ins"

}


SUITE(innovative_path_10_tests) {

    typedef GenericFixture<10, 3> Fixture;

#include "double_path_suite.ins"
#include "float_path_suite.ins"
#include "rational_path_suite.ins"
#include "accuracy_suite.ins"

}

SUITE(innovative_path_15_tests) {

    typedef GenericFixture<15, 2> Fixture;

#include "double_path_suite.ins"
#include "float_path_suite.ins"
#include "rational_path_suite.ins"
#include "accuracy_suite.ins"

}