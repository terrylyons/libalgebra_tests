//
// Created by sam on 12/02/2021.
//


/*
 * Multiplication operator for simple_integer_basis
 */
struct pointwise_multiplication
{
    typedef unsigned key_type;

    template <typename Transform>
    struct key_transform
    {
        key_transform(Transform fn) : m_transform(fn)
        {}

        template <typename Vector, typename Scalar>
        void operator()(
                Vector& result, const key_type& k1, const Scalar& s1, const key_type& k2, const Scalar& s2)
        {
            if (k1 == k2) {
                result.add_scal_prod(k1, m_transform(s1 * s2));
            }
        }

    private:
        Transform m_transform;
    };

    template <typename Algebra, typename Transform>
    void operator()(Algebra& result, const Algebra& lhs, const Algebra& rhs, Transform fn) const
    {
        key_transform<Transform> key_fn(fn);
        lhs.buffered_apply_binary_transform(result, rhs, key_fn);
    }
};


/*
 * The simple algebra basis exercises the square_buffered_apply_binary_transform
 * methods on the underlying vector types. The degree level optimisations can be
 * exercised more readily using the basis classes from libalgebra.
 *
 */
template <DEG Dimension, typename Field>
class simple_algebra_basis : public SimpleIntegerBasis<Dimension, typename Field::Q>
{
#ifndef LIBALGEBRA_ALGEBRA_H
    typedef alg::algebra<simple_algebra_basis, Field,
         //alg::vectors::dense_vector<simple_algebra_basis, Field> > ALG;
         //alg::vectors::sparse_vector<simple_algebra_basis, Field> > ALG;
        ALGEBRA_TESTS_VECT_TYPE < simple_algebra_basis, Field> > ALG;
#endif
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

