//
// Created by sam on 12/02/2021.
//


/*
 * The simple algebra basis exercises the square_buffered_apply_binary_transform
 * methods on the underlying vector types. The degree level optimisations can be
 * exercised more readily using the basis classes from libalgebra.
 *
 */


template <DEG Dimension, typename Field>
class simple_algebra_basis : public SimpleIntegerBasis<Dimension, typename Field::Q>
{
    // We have to jump through some hoops at the moment to get the final algebra type that
    // will be used.
    typedef alg::algebra<simple_algebra_basis, Field,
            ALGEBRA_TESTS_VECT_TYPE<simple_algebra_basis, Field> > ALG;
public:

    typedef typename Field::Q RATIONAL;
    typedef unsigned KEY;

    static const DEG dimension = Dimension;
    static const DEG MAX_DEGREE = 0;

    // Property tags
    typedef alg::basis::without_degree degree_tag;
    typedef alg::basis::ordered<std::less<KEY> > ordering_tag;

    const ALG m_algzero;
    std::vector<ALG> m_mulcache;

    simple_algebra_basis() : m_algzero(), m_mulcache()
    {
        m_mulcache.reserve(Dimension);
        for (KEY i = 0; i < Dimension; ++i) {
            m_mulcache.push_back(ALG(i, typename Field::S(1)));
        }
    }

    const ALG& prod(const KEY& k1, const KEY& k2) const
    {
        if (k1 == k2) {
            return m_mulcache[k1];
        }
        return m_algzero;
    }


};

