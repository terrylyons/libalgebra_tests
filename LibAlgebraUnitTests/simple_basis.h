//
// Created by sam on 02/02/2021.
//

#ifndef LIBALGEBRAUNITTESTS_SIMPLE_BASIS_H
#define LIBALGEBRAUNITTESTS_SIMPLE_BASIS_H

#include <iostream>
#include <utility>

template <unsigned _D>
class SimpleIntegerBasis
{
public:
    static const unsigned dimension = _D;
    typedef unsigned KEY;


    friend std::ostream& operator<<(std::ostream& os,
            const std::pair<SimpleBasis*, KEY> arg) const
    {
        return (os << arg);
    }

};




#endif //LIBALGEBRAUNITTESTS_SIMPLE_BASIS_H
