#include <iostream>

#include <UnitTest++/UnitTest++.h>

#include <libalgebra/libalgebra.h>


#include <libalgebra/alg_types.h>
#include <libalgebra/multiplication_helpers.h>
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

        using SHUFFLE_TENSOR_MULTIPLICATION = alg::shuffle_tensor_multiplication<typename ALG_TYPES::COEFF>;
        typedef typename ALG_TYPES::SHUFFLE_TENSOR SHUFFLE_TENSOR;

        // const TENSOR tunit;
        // const TENSOR tzero;

        const SHUFFLE_TENSOR tunit;
        const SHUFFLE_TENSOR tzero;

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


    TEST_FIXTURE(Fixture, test_product_tunit_zero) {
    TEST_DETAILS();

    // test: {1()} * {} == {1()} // TODO: is this right?

    SHUFFLE_TENSOR lhs(tunit); // {1()}
    SHUFFLE_TENSOR rhs; // {}
    SHUFFLE_TENSOR expected(tunit); // {1()}

    std::cout << "lhs = " << lhs << ", rhs = " << rhs << ", expected = " << expected << std::endl;

    SHUFFLE_TENSOR result;
    // result = lhs * rhs; // TODO: prod doesn't work with * here, error no matching function, expects two args and 1 provided
            
            CHECK_EQUAL(expected, result);

} // TEST test_product_tunit_zero

TEST_FIXTURE(Fixture, test_product_zero_tunit) {
    TEST_DETAILS();

    // test: {} * {1()} == {1()} // TODO: Is this right?

    SHUFFLE_TENSOR lhs; // {}
    SHUFFLE_TENSOR rhs(tunit); // {1()}
    SHUFFLE_TENSOR expected(tunit); // {1()}

    std::cout << "lhs = " << lhs << ", rhs = " << rhs << ", expected = " << expected << std::endl;

    SHUFFLE_TENSOR result;
    // result = lhs * rhs; // TODO: error, expects two args one provided

            CHECK_EQUAL(expected, result);

} // TEST test_product_zero_tunit

TEST_FIXTURE(Fixture, test_product_tunit_tunit) {
    TEST_DETAILS();

    // test: {1()} * {1()} == {1()} // TODO: is this right?

    SHUFFLE_TENSOR lhs(tunit); // {1()}
    SHUFFLE_TENSOR rhs(tunit); // {1()}
    SHUFFLE_TENSOR expected(tunit); // {1()}

    // LET k1[] = {};
    // SHUFFLE_TENSOR expected(k1, 2); // {2()} TODO: think I would use the add scal prod function to put this here, check answer first

    std::cout << "lhs = " << lhs << ", rhs = " << rhs << ", expected = " << expected << std::endl;

    SHUFFLE_TENSOR result;
    // result = lhs * rhs; // TODO: prod doesn't work with * here, error no matching function, expects two args and 1 provided
            
            CHECK_EQUAL(expected, result);

} // TEST test_product_tunit_tunit

TEST_FIXTURE(Fixture, test_product_unidim_deg_1_tunit) {
    TEST_DETAILS();

    // test: {1()} * {1(1)} ==  {1(1)} // TODO: is this right?

    SHUFFLE_TENSOR lhs(tunit); // {1()}
    
    LET k1[] = {1};

    SHUFFLE_TENSOR rhs(make_key(k1, 1)); // {1(1)}

    SHUFFLE_TENSOR expected(make_key(k1, 1)); // {1(1)}
    
    std::cout << "lhs = " << lhs << ", rhs = " << rhs << ", expected = " << expected << std::endl;

    SHUFFLE_TENSOR result;

    // result = lhs * rhs; // TODO

            CHECK_EQUAL(expected, result);

} // TEST test_product_unidim_deg_1_tunit

///////////////////////////////////////////// TODO: trying to use full function calls as well as * overrides /////////////////////////////////////

// struct key_transform
// {
//     template <typename Vector, typename Key, typename Scalar>
//     void operator()(Vector& result, const Key& k1, const Scalar& s1, const Key& k2, const Scalar& s2)
//     {
//         // diagonal multiply
//         if (k1 == k2) {
//             result[k1] += s1 * s2;
//         }
//     }
// };

TEST_FIXTURE(Fixture, test_shuffle_product_unidim_deg_1_1) {
    TEST_DETAILS();

    // test: {1(1)} * {1(2)} == {1(1,2) 1(2,1)} 

    LET k1[] = {1};
    LET k2[] = {2};

    SHUFFLE_TENSOR lhs(make_key(k1, 1)); 
    SHUFFLE_TENSOR rhs(make_key(k2, 1));
    
    std::cout << "lhs: " << lhs << std::endl;
    std::cout << "rhs: " << rhs << std::endl;

    // expected of product { 1(1) } * { 1(2) } = { 1(1,2) 1(2, 1) }
    // as a dense vector {0, 0, ... (width), 0, 1, 0, ...(width), 0, 1, ...(more zeroes) }

    SHUFFLE_TENSOR expected;

    LET k12[] = {1, 2};
    LET k21[] = {2, 1};

    expected.add_scal_prod(make_key(k12,2), 1.0);
    expected.add_scal_prod(make_key(k21,2), 1.0);

    std::cout << "expected: " << expected << std::endl;

    SHUFFLE_TENSOR direct_multiplication = lhs*rhs; // TODO: doesn't work, wrong number of arguments
    // std::cout << "direct_multiplication: " << direct_multiplication << std::endl;
    
    // full function calls attempts

    SHUFFLE_TENSOR_MULTIPLICATION my_shuffle_tensor_product;

    SHUFFLE_TENSOR result;

    alg::mult::scalar_passthrough my_scalar_passthrough; 
    
    // multiply functions - not sure on binary operator "op" argument

    // key_transform kt;
    
    // result = my_shuffle_tensor_product.multiply<SHUFFLE_TENSOR, SHUFFLE_TENSOR, alg::mult::scalar_passthrough>(lhs, rhs, my_scalar_passthrough); // TODO: still doesn't work

    //////////

    std::cout << "result: " << result << std::endl;

            CHECK_EQUAL(expected, result);

    
    } // TEST test_shuffle_product_unidim_deg_1_1

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TEST_FIXTURE(Fixture, test_product_unidim_deg_1_deg_2) {
    TEST_DETAILS();

    // test: {1(1)} * {1(2,3)} == {1(1,2,3) 1(2,1,3) 1(2,3,1)}

    LET k1[] = {1};
    LET k2[] = {2, 3};

    SHUFFLE_TENSOR lhs(make_key(k1, 1)); // {1()1}
    SHUFFLE_TENSOR rhs(make_key(k2, 2)); // {1(2,3)}

    SHUFFLE_TENSOR expected;

    LET k123[] = {1, 2, 3};
    LET k213[] = {2, 1, 3};
    LET k231[] = {2, 3, 1};

    expected.add_scal_prod(make_key(k123,3), 1.0);
    expected.add_scal_prod(make_key(k213,3), 1.0);
    expected.add_scal_prod(make_key(k231,3), 1.0);

    std::cout << "lhs = " << lhs << ", rhs = " << rhs << ", expected = " << expected << std::endl;

    SHUFFLE_TENSOR result;

    // result = lhs * rhs; // TODO: not working

            CHECK_EQUAL(expected, result);

} // TEST test_product_unidim_deg_1_deg_2

TEST_FIXTURE(Fixture, test_product_unidim_deg_2_deg_1) {
    TEST_DETAILS();

    // test: {1(1,2)} * {1(3)} == {1(1,2,3) 1(1,3,2) 1(3,1,2)}

    LET k1[] = {1, 2};
    LET k2[] = {3};

    SHUFFLE_TENSOR lhs(make_key(k1, 2)); // {1(1,2)}
    SHUFFLE_TENSOR rhs(make_key(k2, 1)); // {1(3)}

    SHUFFLE_TENSOR expected;

    LET k123[] = {1, 2, 3};
    LET k132[] = {1, 3, 2};
    LET k312[] = {3, 1, 2};

    expected.add_scal_prod(make_key(k123,3), 1.0);
    expected.add_scal_prod(make_key(k132,3), 1.0);
    expected.add_scal_prod(make_key(k312,3), 1.0);

    std::cout << "lhs = " << lhs << ", rhs = " << rhs << ", expected = " << expected << std::endl;

    SHUFFLE_TENSOR result;

    // result = lhs * rhs; // TODO: not working

            CHECK_EQUAL(expected, result);
            
} // TEST test_product_unidim_deg_2_deg_1

// TEST_FIXTURE(Fixture, test_product_multiple_terms) {
//     TEST_DETAILS();

//     TENSOR lhs(tunit), rhs(tunit);

//     LET letters[] = {1, 2, 3, 4, 4};
//     // 1() + 1(1) + 1(1,2) + 1(1,2,3) + 1(1,2,3,4)
//     for (DEG d=1; d<5; ++d) {
//         lhs += TENSOR(make_key(&letters[0], d));
//     }

//     // 1() + 1(4) + 1(3,4) + 1(2,3,4) + 1(1,2,3,4)
//     for (DEG d=1; d<5; ++d) {
//         rhs += TENSOR(make_key(&letters[4-d], d));
//     }

//     TENSOR expected(tunit);


//     const S one (1);

//     // DEG 5
//     ADD_KEY(5, 1,2,3,4,4);
//     ADD_KEY(5, 1,2,3,3,4);
//     ADD_KEY(5, 1,2,2,3,4);
//     ADD_KEY(5, 1,1,2,3,4);

//     /*
//     expected += TENSOR(make_key((LET[]) {1,2,3,4,4}, 5));
//     expected += TENSOR(make_key((LET[]) {1,2,3,3,4}, 5));
//     expected += TENSOR(make_key((LET[]) {1,2,2,3,4}, 5));
//     expected += TENSOR(make_key((LET[]) {1,1,2,3,4}, 5));
//     */
//     // DEG 4
//     // (1,2,3,4) = () * (1,2,3,4), (1) * (2,3,4), (1,2) * (3,4), (1,2,3) * (4), (1,2,3,4) * ()
//     {
//         LET tmp[] = {1,2,3,4};
//         expected.add_scal_prod(make_key(tmp, 4), S(5));
//     }

//     // DEG 3
//     ADD_KEY(3, 1,2,3);
//     ADD_KEY(3, 1,2,4);
//     ADD_KEY(3, 1,3,4);
//     ADD_KEY(3, 2,3,4);
//     /*
//     expected += TENSOR(make_key((LET[]) {1,2,3}, 3));
//     expected += TENSOR(make_key((LET[]) {1,2,4}, 3));
//     expected += TENSOR(make_key((LET[]) {1,3,4}, 3));
//     expected += TENSOR(make_key((LET[]) {2,3,4}, 3));
// */

//     // DEG 2
//     ADD_KEY(2, 1,2);
//     ADD_KEY(2, 1,4);
//     ADD_KEY(2, 3,4);
//     /*
//     expected += TENSOR(make_key((LET[]) {1,2}, 2));
//     expected += TENSOR(make_key((LET[]) {1,4}, 2));
//     expected += TENSOR(make_key((LET[]) {3,4}, 2));
// */

//     // DEG 1
//     expected += TENSOR(KEY(LET(1)));
//     expected += TENSOR(KEY(LET(4)));

//     #undef ADD_KEY

//     CHECK_EQUAL(expected, lhs * rhs);
// }


} // SUITE shuffle_tensor
