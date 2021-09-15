#include <UnitTest++/UnitTest++.h>

#include <libalgebra/libalgebra.h>


#include <libalgebra/alg_types.h>

#include "../time_and_details.h"


#include <libalgebra/tensor.h>

using alg::LET;
using alg::DEG;
using alg::shuffle_tensor;
using alg::shuffle_tensor_multiplication;

SUITE(shuffle_tensor)
{
    // TODO: Change this to provide a SHUFFLE_TENSOR 

    struct Fixture : public alg_types<5, 5, Rational>
    {
        typedef alg_types<5, 5, Rational> ALG_TYPES;
        typedef typename ALG_TYPES::TENSOR TENSOR;
        typedef typename TENSOR::BASIS TBASIS;
        typedef typename TENSOR::KEY KEY;

        const TENSOR tunit;
        const TENSOR tzero;

        Fixture() : tunit(KEY()), tzero()
        {}

        KEY make_key(const LET* arg, const std::size_t N)
        {
            KEY k;
            for (std::size_t i=0; i<N; ++i) {
                k.push_back(arg[i]);
            }
            return k;
        }

    };

#define ADD_KEY(N, ...) \
    {                     \
        LET tmp[N] = {__VA_ARGS__};  \
        expected += TENSOR(make_key(tmp, N));\
    }

TEST_FIXTURE(Fixture, test_shuffle_product_unidim_deg_1_1) {
    TEST_DETAILS();

    LET k1[] = {1};
    LET k2[] = {2};

    typedef alg::coefficients::coefficient_field<double> double_field;

    shuffle_tensor<double_field, 5, 5> lhs(make_key(k1, 1));

    shuffle_tensor<double_field, 5, 5> rhs(make_key(k2, 1));

    shuffle_tensor<double_field, 5, 5> expected;

    LET k12[] = {1, 2};
    LET k21[] = {2, 1};

    expected.add_scal_prod(make_key(k12,2), 1.0);
    expected.add_scal_prod(make_key(k21,2), 1.0);
    
    // expected of product { 1(1) } * { 1(2) } = { 1(1,2) 1(2, 1) }
    // as a dense vector {0, 0, ... (width), 0, 1, 0, ...(width), 0, 1, ...(more zeroes) }

    shuffle_tensor_multiplication<double_field> shuffle_tensor_product;

    shuffle_tensor<double_field, 5, 5> result;

    // product = shuffle_tensor_product._prod<shuffle_tensor<double_field, 5, 5>>(lhs, rhs);

    // result = shuffle_tensor_product.multiply<tAlgebra, tAlgebra, tOperator>(lhs, rhs, op);

            CHECK_EQUAL(expected, result);

    // CHECK_EQUAL(1, 1);
    
    }
}