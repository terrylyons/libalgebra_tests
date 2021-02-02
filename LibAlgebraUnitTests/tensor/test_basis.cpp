//
// Created by sam on 02/02/2021.
//

#include <UnitTest++/UnitTest++.h>

#include <libalgebra/libalgebra.h>

#include "../time_and_details.h"

using alg::DEG;
using alg::LET;

template <typename S, typename R, DEG W, DEG D>
struct BasisTool
{
    typedef alg::tensor_basis<S, W, D> TBASIS;
    typedef alg::free_tensor_basis<S, R, W, D> FTBASIS;
    typedef alg::shuffle_tensor_basis<S, R, W, D> STBASIS;
    typedef typename TBASIS::KEY KEY;

    template <std::size_t N>
    KEY make_key(std::array<LET, N> letters)
    {
        KEY k;
        for (int i=0; i<N; ++i)
            k.push_back(letters[i]);
        return k;
    }

};

struct Framework55Double : public BasisTool<double, double, 5, 5>
{
    typedef BasisTool<double, double, 5, 5> TOOL;
    typedef typename TOOL::TBASIS TBASIS;
    typedef typename TOOL::FTBASIS FTBASIS;
    typedef typename TOOL::STBASIS STBASIS;
    typedef typename TOOL::KEY KEY;
};


SUITE (tensor_basis) {


    TEST_FIXTURE(Framework55Double, test_degree) {
        TEST_DETAILS();

        KEY k;
        TBASIS basis;

        CHECK_EQUAL(0, basis.degree(k));

        for (DEG d=1; d<=5; ++d) {
            k.push_back(LET(1));
            CHECK_EQUAL(d, basis.degree(k));
        }

    }

    TEST_FIXTURE(Framework55Double, test_begin_key_empty) {
        TEST_DETAILS();
        TBASIS basis;

        CHECK_EQUAL(KEY(), basis.begin());
    }

    /*
    TEST_FIXTURE(Framework55Double, test_last_key) {
        TEST_DETAILS()

        TBASIS basis;

        std::array<LET, 5> letters  {4, 4, 4, 4, 4};
        CHECK_EQUAL(make_key(letters), basis.end());
    }
    */

    TEST_FIXTURE(Framework55Double, test_next_key) {
        TEST_DETAILS()

        TBASIS basis;

        std::array<LET, 3> letters {1, 2, 3}, exp_letters {1, 2, 4};

        KEY k = make_key(letters);

        CHECK_EQUAL(make_key(exp_letters), basis.nextkey(k));

    }
}


SUITE(free_tensor_basis) {

    TEST_FIXTURE(Framework55Double, test_prod_empty_keys) {
        TEST_DETAILS()

        FTBASIS basis;
        KEY k1, k2, expected;

        CHECK_EQUAL(expected, basis.prod(k1, k2));

    }

    TEST_FIXTURE(Framework55Double, test_prod_empty_deg1) {
        TEST_DETAILS()

        FTBASIS basis;

        KEY k1;
        std::array<LET, 1> let2 {1};
        std::array<LET, 1> elet {1};
        KEY expected = make_key(elet);

        CHECK_EQUAL(expected, basis.prod(make_key(let2), k1));
        CHECK_EQUAL(expected, basis.prod(k1, make_key(let2)));
    }

    TEST_FIXTURE(Framework55Double, test_prod_deg1_deg1) {
        TEST_DETAILS()

        FTBASIS basis;
        std::array<LET, 1> let1 {1};
        std::array<LET, 1> let2 {2};
        std::array<LET, 2> elet {1, 2};

        KEY expected = make_key(elet);
        KEY result = basis.prod(make_key(let1), make_key(let2));

        CHECK_EQUAL((DEG) 2, basis.degree(result));
        CHECK_EQUAL(expected, result);
    }

    TEST_FIXTURE(Framework55Double, test_prod_deg1_deg2) {
        TEST_DETAILS()

        FTBASIS basis;
        std::array<LET, 1> let1 {1};
        std::array<LET, 2> let2 {2, 3};
        std::array<LET, 3> elet {1, 2, 3};

        KEY expected = make_key(elet);
        KEY result = basis.prod(make_key(let1), make_key(let2));

        CHECK_EQUAL((DEG) 3, basis.degree(result));
        CHECK_EQUAL(expected, result);
    }




}