//
// Created by sam on 04/02/2021.
//

#include <random>
#include <vector>
#include <map>

#include <UnitTest++/UnitTest++.h>

#include <libalgebra/libalgebra.h>
#include <libalgebra/alg_types.h>

#include "../time_and_details.h"

using alg::LET;
using alg::DEG;

SUITE (hybrid_tensor_multiplication) {

    struct Fixture : public alg_types<5, 5, Rational>
    {
        typedef alg_types<5, 5, Rational> ALG_TYPES;

        typedef typename ALG_TYPES::TENSOR::BASIS TBASIS;
        typedef typename TBASIS::KEY TKEY;

        struct field
        {
            typedef typename ALG_TYPES::S S;
            typedef typename ALG_TYPES::Q Q;
        };

        typedef alg::vectors::hybrid_vector<
                TBASIS,
                field,
                alg::vectors::basic_resize_manager,
                std::vector<typename field::S>,
                std::map<TKEY, typename field::S>
                > DENSE;
        typedef alg::algebra<TBASIS, field, DENSE> TENSOR;

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

        TKEY make_key(const LET* arg, const std::size_t N)
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


    TEST_FIXTURE(Fixture, test_product_unidim_deg_3_deg_3_overflow_removed) {
        TEST_DETAILS();

        std::array<LET, 3> k1 {1, 2, 3};
        std::array<LET, 3> k2 {1, 2, 3};
        TENSOR lhs(make_key(k1)), rhs(make_key(k2));

        TENSOR expected(tzero);

        CHECK_EQUAL(expected, lhs * rhs);
    }

    TEST_FIXTURE(Fixture, test_product_multiple_terms) {
        TEST_DETAILS();

        TENSOR lhs(tunit), rhs(tunit);

        std::array<LET, 5> letters {1, 2, 3, 4, 4};
        // 1() + 1(1) + 1(1,2) + 1(1,2,3) + 1(1,2,3,4)
        for (DEG d=1; d<5; ++d) {
            lhs += TENSOR(make_key(&letters[0], d));
        }

        // 1() + 1(4) + 1(3,4) + 1(2,3,4) + 1(1,2,3,4)
        for (DEG d=1; d<5; ++d) {
            rhs += TENSOR(make_key(&letters[4-d], d));
        }

        TENSOR expected(tunit);

        // DEG 5
        expected += TENSOR(make_key(letters));
        letters = {1,2,3,3,4};
        expected += TENSOR(make_key(letters));
        letters = {1,2,2,3,4};
        expected += TENSOR(make_key(letters));
        letters = {1,1,2,3,4};
        expected += TENSOR(make_key(letters));

        letters = {1,2,3,4,0};
        // (1,2,3,4) = () * (1,2,3,4), (1) * (2,3,4), (1,2) * (3,4), (1,2,3) * (4), (1,2,3,4) * ()
        expected.add_scal_prod(make_key(&letters[0], 4), S(5));

        // DEG 3
        letters = {1,2,3,0,0};
        expected += TENSOR(make_key(&letters[0], 3));
        letters = {1,2,4,0,0};
        expected += TENSOR(make_key(&letters[0], 3));
        letters = {1,3,4,0,0};
        expected += TENSOR(make_key(&letters[0], 3));
        letters = {2,3,4,0 ,0};
        expected += TENSOR(make_key(&letters[0], 3));

        // DEG 2
        letters = {1,2,0,0,0};
        expected += TENSOR(make_key(&letters[0], 2));
        letters = {1,4,0,0,0};
        expected += TENSOR(make_key(&letters[0], 2));
        letters = {3,4,0,0,0};
        expected += TENSOR(make_key(&letters[0], 2));

        // DEG 1
        expected += TENSOR(TKEY(LET(1)));
        expected += TENSOR(TKEY(LET(4)));

        CHECK_EQUAL(expected, lhs * rhs);
    }




}