//
// Created by sam on 23/03/2021.
//

#include <map>

#include <UnitTest++/UnitTest++.h>

#include <libalgebra/libalgebra.h>
#include <libalgebra/alg_types.h>

#include "../time_and_details.h"
#include "../helpers.h"




template <typename Coeff, unsigned Width, unsigned Depth>
struct fixture
{


    typedef typename Coeff::S S;
    typedef typename Coeff::Q Q;

    typedef alg::free_tensor_basis<S, Q, Width, Depth> TBASIS;
    typedef typename TBASIS::KEY KEY;
    typedef alg::vectors::sparse_vector<TBASIS, Coeff, std::map<KEY, S> > VECT;
    typedef alg::free_tensor<S, Q, Width, Depth, VECT> TENSOR;


    template<class T>
    T exp_to_depth(T x, S one) {
        T result (one);
        T tone(S(1));

        for (size_t i=Depth; i>=1; --i) {
            result *= (x / Q(i));
            result += tone;
        }
        return result;
    }

    TENSOR log_to_depth(const TENSOR& x) {
        TENSOR result;

        KEY kunit;
        TENSOR tunit(kunit);

        TENSOR xx(x);
        typename TENSOR::iterator it(xx.find(KEY()));
        if (it != xx.end()) {
            xx.erase(it);
        }


        for (unsigned i = Depth; i >= 1; --i) {

            if (i % 2 == 0) {
                result -= (tunit / Q(i));
            } else {
                result += (tunit / Q(i));
            }
            result *= xx;
        }
        return result;
    }

};



SUITE(sparse_tensor_functions_float) {

    struct float_field {
        typedef float S;
        typedef float Q;
    };

    static const double expected_error = 3e-8f;
    typedef fixture<float_field, 5, 5> fixture;

#include "tensor_exp_suite.h"
#include "tensor_log_suite.h"
#include "tensor_inverse_suite.h"
#include "tensor_roundtrip_suite.h"


}


SUITE(sparse_tensor_functions_double) {

    struct double_field {
        typedef double S;
        typedef double Q;
    };

    typedef fixture<double_field, 5, 5> fixture;
    static const double expected_error = 2e-15;

#include "tensor_exp_suite.h"
#include "tensor_log_suite.h"
#include "tensor_inverse_suite.h"
#include "tensor_roundtrip_suite.h"
}




SUITE(sparse_tensor_functions_rational) {

    struct rational_field {
        typedef mpq_class S;
        typedef mpq_class Q;
    };

    typedef fixture<rational_field, 5, 5> fixture;
    static const double expected_error = 0.0;

#include "tensor_exp_suite.h"
#include "tensor_log_suite.h"
#include "tensor_inverse_suite.h"
#include "tensor_roundtrip_suite.h"
}
