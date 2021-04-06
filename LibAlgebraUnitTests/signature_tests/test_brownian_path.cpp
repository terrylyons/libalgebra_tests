//
// Created by sam on 16/03/2021.
//

#include <algorithm>
#include <cmath>
#include <vector>
#include <exception>
#include <map>

#pragma warning(suppress:4616) 
#include <boost/math/common_factor_rt.hpp> // deprecated
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/special_functions/modf.hpp>
#include <UnitTest++/UnitTest++.h>

#include <libalgebra/libalgebra.h>
#include <libalgebra/alg_types.h>

#include "../time_and_details.h"
#include "../rng.h"
#include "../helpers.h"

#include "generic_coefficient.h"
#include "generic_lie_increment.h"
#include "generic_path.h"

namespace {

    template <typename Integer>
    generic_coefficient<Integer> convert_to_generic(double arg, Integer prec)
    {
        double integ = NAN;
        double fract = boost::math::modf(arg, &integ);

        assert (!boost::math::isnan(integ));

        Integer integral_part = static_cast<Integer>(integ);
        Integer scaled_fract = static_cast<Integer>(round(fract * static_cast<double>(prec)));

        Integer gcd1 = boost::math::gcd(scaled_fract, prec);
        assert (gcd1 != 0);

        Integer fract_part_num = scaled_fract / gcd1;
        Integer fract_part_den = prec / gcd1;

        Integer tmp = fract_part_den * integral_part + fract_part_num;
        Integer gcd2 = boost::math::gcd(tmp, fract_part_den);
        assert (gcd2 != 0);

        return generic_coefficient<Integer>(tmp / gcd2, fract_part_den / gcd2);
    }

}

template <unsigned Width, typename Integer, typename Rng>
inline generic_lie_increment<Width, Integer>
make_brownian_increment(double stdev, Rng rng)
{
    std::vector<generic_coefficient<Integer> > tmp;
    tmp.reserve(Width);

    NORMAL_DIST<double> normal(0.0, stdev);

    for (unsigned i=0; i < Width; ++i) {
        tmp.push_back(convert_to_generic<Integer>(normal(rng), 1000));
    }

    return generic_lie_increment<Width, Integer>(tmp);
}


template <unsigned Width>
generic_path<Width> make_brownian_path(unsigned length=Width)
{
    assert (length > 0);
    std::vector<generic_lie_increment<Width, int32_t> > tmp;
    tmp.reserve(length);

    mt19937 rng(12345);
    double stdev = 1.0 / sqrt(static_cast<double>(length));

    for (std::size_t i=0; i<length; ++i) {
        generic_lie_increment<Width, int32_t> incr (make_brownian_increment<Width, int32_t>(stdev, rng));
        tmp.push_back(incr);
    }

    return generic_path<Width>(tmp);
}


template <unsigned Width, unsigned Depth, unsigned Length>
struct GenericFixture
{
    static const unsigned width = Width;
    static const unsigned depth = Depth;
    static const unsigned length = Length;

    generic_path<Width> path;


    float expected_float_error;
    double expected_double_error;


    struct rational_field
    {
        typedef mpq_class S;
        typedef mpq_class Q;
    };

    struct rational_sparse_framework
    {
        typedef typename rational_field::S S;
        typedef typename rational_field::Q Q;
        typedef alg::free_tensor_basis<S, Q, width, depth> TBASIS;
        typedef alg::lie_basis<S, Q, width, depth> LBASIS;

        typedef alg::vectors::sparse_vector<
                TBASIS,
                alg::TrivialCoeffs<TBASIS>,
                std::map < typename TBASIS::KEY, S>
        > SPTENS;

        typedef alg::vectors::sparse_vector<
                LBASIS,
                alg::TrivialCoeffs<LBASIS>,
                std::map < typename LBASIS::KEY, S>
        > SPLIE;

        typedef alg::free_tensor<S, Q, width, depth, SPTENS> TENSOR;
        typedef alg::lie<S, Q, width, depth, SPLIE> LIE;
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

    GenericFixture() : path(make_brownian_path<Width>(Length)),
                       expected_double_error(2.0e-12),
                       expected_float_error(7.0e-4f)
    {}

    size_t sig_support(unsigned increments=length)
    {
        if (increments == 0) {
            return 1;
        } else {
            typename rational_dense_framework::TBASIS basis;
            return basis.start_of_degree(depth+1);
        }

    }

};

SUITE(brownian_path_5_5_10_tests) {

    typedef GenericFixture<5U, 5U, 10U> Fixture;

#include "double_path_suite.ins"
#include "float_path_suite.ins"
#include "rational_path_suite.ins"
#include "accuracy_suite.ins"

}



SUITE(brownian_path_5_5_50_tests) {

typedef GenericFixture<5U, 5U, 50U> Fixture;

#include "double_path_suite.ins"
#include "float_path_suite.ins"
#include "rational_path_suite.ins"
#include "accuracy_suite.ins"

}



SUITE(brownian_path_10_2_10_tests) {

typedef GenericFixture<10, 2, 10> Fixture;

#include "double_path_suite.ins"
#include "float_path_suite.ins"
#include "rational_path_suite.ins"
#include "accuracy_suite.ins"

}
