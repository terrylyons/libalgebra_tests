//
// Created by sam on 11/03/2021.
//

#ifndef LIBALGEBRAUNITTESTS_GENERIC_LIE_INCREMENT_H
#define LIBALGEBRAUNITTESTS_GENERIC_LIE_INCREMENT_H

#include <vector>

#include "generic_coefficient.h"

template <unsigned Width, typename Integer>
class generic_lie_increment : std::vector<generic_coefficient<Integer> >
{
    typedef std::vector<generic_coefficient<Integer> > BASE;
public:

    using BASE::operator[];

    generic_lie_increment() : BASE(Width)
    {}

    template <typename Lie>
    Lie to_lie() const
    {
        assert( BASE::size() == Width);
        typedef typename Lie::KEY Key; // size_t
        typedef typename Lie::SCALAR Scalar;
        Lie result;
        for (Key i=0; i<Width; ++i) {
            // zero is not a valid Lie key.
            result.add_scal_prod(i+1, Scalar(operator[](i)));
        }
        return result;
    }

};




#endif //LIBALGEBRAUNITTESTS_GENERIC_LIE_INCREMENT_H
