//
// Created by sam on 18/02/2021.
//

#ifndef LIBALGEBRAUNITTESTS_COMPAT_H
#define LIBALGEBRAUNITTESTS_COMPAT_H

#include <iterator>
#include <utility>

#include <libalgebra/utils/meta.h>
#include <libalgebra/vectors/iterators.h>

#include <boost/type_traits.hpp>
#include <boost/mpl/logical.hpp>


namespace iter {

#define ENABLE_IF_PAIR(OTYPE, VTYPE, KT, VT)                                    \
    typename boost::enable_if<                                                  \
        typename boost::mpl::and_<                                              \
            typename boost::is_same<                                            \
                typename boost::remove_cv<typename VTYPE ::first_type>::type,   \
                KT                                                              \
            >::type,                                                            \
            typename boost::is_same<                                            \
                typename boost::remove_cv<typename VTYPE ::second_type>::type,  \
                VT                                                              \
            >::type                                                             \
        >::type,                                                                \
        OTYPE                                                                   \
    >::type


template <typename Vector,
        typename Iterator,
        typename ValueType = typename std::iterator_traits<Iterator>::value_type,
        typename Reference = typename std::iterator_traits<Iterator>::reference>
ENABLE_IF_PAIR(typename Vector::KEY, ValueType, typename Vector::KEY, typename Vector::SCALAR)
key(Iterator& it)
{ return it->first; }

template <typename Vector,
        typename Iterator,
        typename ValueType = typename std::iterator_traits<Iterator>::value_type,
        typename Reference = typename std::iterator_traits<Iterator>::reference,
        typename OutType = typename alg::utils::copy_constness<Reference, typename Vector::SCALAR>::type >
ENABLE_IF_PAIR(OutType, ValueType, typename Vector::KEY, typename Vector::SCALAR)
value(Iterator& it)
{ return it->second; }



#undef ENABLE_IF_PAIR

template <typename Vector, typename ValueType>
typename ValueType::key_type key(alg::vectors::iterators::vector_iterator<ValueType>& it)
{
    return it->key();
}

template <typename Vector, typename ValueType>
typename ValueType::value_type value(alg::vectors::iterators::vector_iterator<ValueType>& it)
{
    return it->value();
}


}


#endif //LIBALGEBRAUNITTESTS_COMPAT_H
