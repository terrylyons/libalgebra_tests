//
// Created by sam on 03/02/2021.
//

#include <random>
#include <unordered_map>

#include <UnitTest++/UnitTest++.h>

#include "../simple_basis.h"
#include "../time_and_details.h"
#include <libalgebra/alg_types.h>
#include "../compat.h"

#ifdef LIBALGEBRA_VECTORS_H



using alg::vectors::hybrid_vector;


#define _VECTOR_TYPE hybrid_vector
#define _VECTOR_TYPE_ADDITIONAL_PARAMS                                      \
    alg::vectors::basic_resize_manager,                                     \
    std::vector<typename FIELD::S>,                                         \
    std::unordered_map<typename BASIS::KEY, typename FIELD::S>
#define _TVECTOR_TYPE_ADDITIONAL_PARAMS                                      \
    alg::vectors::basic_resize_manager,                                     \
    std::vector<typename FIELD::S>,                                         \
    std::unordered_map<typename TBASIS::KEY, typename FIELD::S, typename TBASIS::KEY::hash>

SUITE(hybrid_vector) {

#include "framework_fixture.h"
#include "vector_arithmetic_suite.h"
#include "vector_comparison_suite.h"
#include "vector_element_access_suite.h"
#include "vector_iterator_suite.h"
#include "vector_properties_suite.h"
#include "vector_norm_suite.h"
#include "vector_binary_transform_suite.h"

}


#undef _VECTOR_TYPE_ADDITIONAL_PARAMS
#undef _VECTOR_TYPE

#endif