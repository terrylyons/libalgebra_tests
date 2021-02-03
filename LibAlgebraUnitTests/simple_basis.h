//
// Created by sam on 02/02/2021.
//

#ifndef LIBALGEBRAUNITTESTS_SIMPLE_BASIS_H
#define LIBALGEBRAUNITTESTS_SIMPLE_BASIS_H

#include <iostream>
#include <utility>

template <unsigned _D, typename _R>
class SimpleIntegerBasis
{
public:
    static const unsigned dimension = _D;
    typedef unsigned KEY;
    typedef _R RATIONAL;


    friend std::ostream& operator<<(std::ostream& os,
            const std::pair<SimpleIntegerBasis*, KEY> arg)
    {
        return (os << arg.second);
    }

};




#endif //LIBALGEBRAUNITTESTS_SIMPLE_BASIS_H
