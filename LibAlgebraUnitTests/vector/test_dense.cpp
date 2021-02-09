//
// Created by sam on 03/02/2021.
//

#include <random>
#include <unordered_map>

#include <UnitTest++/UnitTest++.h>

#include "../simple_basis.h"
#include "../time_and_details.h"
#include <libalgebra/alg_types.h>
#include <libalgebra/libalgebra.h>

#ifdef LIBALGEBRA_VECTORS_H
using alg::vectors::dense_vector;


#define _VECTOR_TYPE dense_vector
#undef _VECTOR_TYPE_ADDITIONAL_PARAMS

SUITE(dense_vector) {

#include "framework_fixture.h"
#include "vector_arithmetic_suite.h"
#include "vector_comparison_suite.h"
#include "vector_element_access_suite.h"
//#include "vector_iterator_suite.h"
#include "vector_properties_suite.h"

}


#undef _VECTOR_TYPE_ADDITIONAL_PARAMS
#undef _VECTOR_TYPE
#endif