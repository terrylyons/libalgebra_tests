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

    KEY make_key(const LET* letters, std::size_t N)
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

        LET in[] = {1,2,3};
        KEY k = make_key(in,3);

        LET expected[] = {1,2,4};
        CHECK_EQUAL(make_key(expected, 3), basis.nextkey(k));

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
        KEY expected = KEY(LET(1));

        CHECK_EQUAL(expected, basis.prod(KEY(LET(1)), k1));
        CHECK_EQUAL(expected, basis.prod(k1, KEY(LET(1))));
    }

    TEST_FIXTURE(Framework55Double, test_prod_deg1_deg1) {
        TEST_DETAILS()

        FTBASIS basis;

        LET expected_let[] = {1,2};
        KEY expected = make_key(expected_let, 2);
        KEY result = basis.prod(KEY(LET(1)), KEY(LET(2)));

        CHECK_EQUAL((DEG) 2, basis.degree(result));
        CHECK_EQUAL(expected, result);
    }

    TEST_FIXTURE(Framework55Double, test_prod_deg1_deg2) {
        TEST_DETAILS()

        FTBASIS basis;

        LET rhs_let[] = {2,3};
        LET expected_let[] = {1,2,3};
        KEY expected = make_key(expected_let, 3);
        KEY result = basis.prod(KEY(LET(1)), make_key(rhs_let, 2));

        CHECK_EQUAL((DEG) 3, basis.degree(result));
        CHECK_EQUAL(expected, result);
    }




}