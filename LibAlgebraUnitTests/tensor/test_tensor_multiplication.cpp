//
// Created by sam on 04/02/2021.
//

#include <UnitTest++/UnitTest++.h>

#include <libalgebra/libalgebra.h>
#include <libalgebra/alg_types.h>

#include "../time_and_details.h"

using alg::LET;
using alg::DEG;

SUITE (tensor_multiplication) {

    struct Fixture : public alg_types<5, 5, Rational>
    {
        typedef alg_types<5, 5, Rational> ALG_TYPES;
        typedef typename ALG_TYPES::TENSOR TENSOR;
        typedef typename TENSOR::BASIS TBASIS;
        typedef typename TENSOR::KEY TKEY;

        const TENSOR tunit;
        const TENSOR tzero;

        Fixture() : tunit(TKEY()), tzero()
        {}

        template <std::size_t N>
        TKEY make_key(std::array<LET, N> arg)
        {
            TKEY k;
            for (std::size_t i=0; i<N; ++i) {
                k.push_back(arg[i]);
            }
            return k;
        }


    };

    TEST_FIXTURE(Fixture, test_product_tunit_tunit) {
        TEST_DETAILS();

        TENSOR lhs(tunit), rhs(tunit);

        CHECK_EQUAL(tunit, lhs * rhs);
    }

    TEST_FIXTURE(Fixture, test_product_unidim_deg_1_tunit) {
        TEST_DETAILS();

        std::array<LET, 1> k1 {1};

        TENSOR lhs(tunit), rhs(make_key(k1));

        TENSOR expected(rhs);
        CHECK_EQUAL(expected, lhs * rhs);
    }

    TEST_FIXTURE(Fixture, test_product_unidim_deg_1_1) {
        TEST_DETAILS();

        std::array<LET, 1> k1 {1};
        std::array<LET, 1> k2 {2};
        TENSOR lhs(make_key(k1)), rhs(make_key(k2));

        std::array<LET, 2> ek {1, 2};
        TENSOR expected(make_key(ek));

        CHECK_EQUAL(expected, lhs * rhs);
    }

    TEST_FIXTURE(Fixture, test_product_unidim_deg_1_deg_2) {
        TEST_DETAILS();

        std::array<LET, 1> k1 {1};
        std::array<LET, 2> k2 {2, 3};
        TENSOR lhs(make_key(k1)), rhs(make_key(k2));

        std::array<LET, 3> ek {1, 2, 3};
        TENSOR expected(make_key(ek));

        CHECK_EQUAL(expected, lhs * rhs);
    }

    TEST_FIXTURE(Fixture, test_product_unidim_deg_2_deg_1) {
        TEST_DETAILS();

        std::array<LET, 2> k1 {1, 2};
        std::array<LET, 1> k2 {3};
        TENSOR lhs(make_key(k1)), rhs(make_key(k2));

        std::array<LET, 3> ek {1, 2, 3};
        TENSOR expected(make_key(ek));

        CHECK_EQUAL(expected, lhs * rhs);
    }

}