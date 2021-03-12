//
// Created by sam on 11/03/2021.
//

#ifndef LIBALGEBRAUNITTESTS_GENERIC_PATH_H
#define LIBALGEBRAUNITTESTS_GENERIC_PATH_H

#include <vector>
#include <utility>
#include <functional>
#include <stdint.h>

#include "../memfile.h"

#include "generic_lie_increment.h"

template <unsigned Width>
class generic_path
{
    std::vector<generic_lie_increment<Width, std::int32_t> > m_increments;
public:

    generic_path(std::vector<generic_lie_increment<Width, std::int32_t> > increments)
        : m_increments(increments)
    {
    }

    size_t length() const
    {
        return m_increments.size();
    }

    template <typename Framework>
    typename Framework::TENSOR signature(size_t start_increment=0, size_t end_increment=-1) const
    {
        typedef typename Framework::TENSOR Tensor;
        typedef typename Framework::LIE Lie;
        typename Framework::MAPS maps;

        size_t end = std::min(end_increment, m_increments.size());

        Tensor result(typename Tensor::SCALAR(1));
        for (size_t i=start_increment; i<end; ++i) {
            result *= exp(maps.l2t(m_increments[i].template to_lie<Lie>()));
        }
        return result;
    }

    template <typename Framework>
    typename Framework::LIE log_signature(size_t start_increment=0, size_t end_increment=-1) const
    {
        typename Framework::MAPS maps;
        return maps.t2l(log(signature<Framework>(start_increment, end_increment)));
    }

};





#endif //LIBALGEBRAUNITTESTS_GENERIC_PATH_H
