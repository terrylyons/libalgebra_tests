//
// Created by sam on 03/02/2021.
//

#include <random>
#include <unordered_map>

#include <UnitTest++/UnitTest++.h>

#include "../simple_basis.h"
#include "../time_and_details.h"
#include <libalgebra/alg_types.h>

using alg::sparse_vector;

#define _VECTOR_TYPE sparse_vector
#define _VECTOR_TYPE_ADDITIONAL_PARAMS std::unordered_map<typename BASIS::KEY, typename FIELD::S>

SUITE(sparse_vector) {

#include "framework_fixture.h"
#include "vector_arithmetic_suite.h"
#include "vector_comparison_suite.h"


}


#undef _VECTOR_TYPE_ADDITIONAL_PARAMS
#undef _VECTOR_TYPE