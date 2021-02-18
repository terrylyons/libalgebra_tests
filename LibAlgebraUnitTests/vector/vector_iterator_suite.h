//
// Created by sam on 03/02/2021.
//

#if 0
#undef TEST_FIXTURE
#undef CHECK_EQUAL
#define CHECK_EQUAL CHECK_EQUAL
#define TEST_FIXTURE(F, N) void N()
#endif

#if defined(_VECTOR_TYPE)

#define GENERATE_ITERATOR_TESTS(IT_TYPE, BEGIN, END)                \
    TEST_FIXTURE(Fixture, test_ ## IT_TYPE ## _unidim_not_equal) {  \
        TEST_DETAILS();                                             \
        VECT vect(KEY(1));                                          \
                                                                    \
        typename VECT:: IT_TYPE it(vect. BEGIN()), itend(vect. END());\
        CHECK(it != itend);                                         \
    }                                                               \
                                                                    \
    TEST_FIXTURE(Fixture, test_ ## IT_TYPE ## _element_access) {    \
        TEST_DETAILS();                                             \
        VECT vect(rand_vec(S(1), S(5)));                            \
        typename VECT:: IT_TYPE it(vect. BEGIN()), end(vect. END());  \
                                                                    \
        for (KEY i=0; i<BASIS::dimension; ++i) {                    \
            REQUIRE CHECK(it != end);                               \
            CHECK_EQUAL(                                            \
                vect[iter::key<VECT>(it)],                          \
                iter::value<VECT>(it)                               \
            );                                                      \
            ++it;                                                   \
        }                                                           \
    }


    GENERATE_ITERATOR_TESTS(iterator, begin, end);
    GENERATE_ITERATOR_TESTS(const_iterator, cbegin, cend);


#undef GENERATOR_ITERATOR_TESTS


// For non-const iterators only
TEST_FIXTURE(Fixture, test_iterator_element_modification) {
    TEST_DETAILS();
    VECT vect(rand_vec());
    KEY k(3);
    S old_val = vect[k];

    typename VECT::iterator it(vect.begin());
    REQUIRE CHECK(it != vect.end());
    while (iter::key<VECT>(it) != k) {
        ++it;
        REQUIRE CHECK(it != vect.end());
    }
    REQUIRE CHECK_EQUAL(k, iter::key<VECT>(it));
    REQUIRE CHECK_EQUAL(old_val, iter::value<VECT>(it));

    iter::value<VECT>(it) = S(6.5); // Out of range of the randomly generated elements

    CHECK_EQUAL(S(6.5), vect[k]);
}

TEST_FIXTURE(Fixture, test_insert_vector_iterator) {
    TEST_DETAILS();

    std::vector<std::pair<KEY, S>> tmp;
    tmp.reserve(BASIS::dimension);
    for (KEY i=0; i<BASIS::dimension; ++i) {
        tmp.push_back(std::pair<KEY, S>(i, rand_scalar()));
    }

    VECT vect; // empty
    REQUIRE CHECK(vect.empty());

    vect.insert(tmp.begin(), tmp.end());

    for (KEY i=0; i<BASIS::dimension; ++i) {
        CHECK_EQUAL(tmp[i].second, vect[i]);
    }
}

TEST_FIXTURE(Fixture, test_insert_from_pair) {
    TEST_DETAILS();

    std::pair<const KEY, S> pair(KEY(1), rand_scalar());
    VECT vect;
    REQUIRE CHECK(vect.empty());

    std::pair<typename VECT::iterator, bool>
        out = vect.insert(pair);

    CHECK(out.second);
    CHECK_EQUAL(pair.first, iter::key<VECT>(out.first));
    CHECK_EQUAL(pair.second, iter::value<VECT>(out.first));
}

TEST_FIXTURE(Fixture, test_insert_fails_already_occupied) {
    TEST_DETAILS();

    std::pair<const KEY, S> pair(KEY(1), S(6)); // 6 is greater than bound
    VECT vect(rand_vec());

    std::pair<typename VECT::iterator, bool>
            out = vect.insert(pair);

    CHECK(!out.second);
    CHECK(vect[KEY(1)] != S(6));
}

TEST_FIXTURE(Fixture, test_iterator_find_key_unidim) {
        TEST_DETAILS();
        VECT vect(KEY(1));
        typename VECT::iterator it(vect.find(KEY(1)));

        REQUIRE CHECK(it != vect.end());

        CHECK_EQUAL(KEY(1), iter::key<VECT>(it));
        CHECK_EQUAL(vect[KEY(1)], iter::value<VECT>(it));
    }

TEST_FIXTURE(Fixture, test_iterator_find_key_full_vec) {
        TEST_DETAILS();
        VECT vect(rand_vec());
        typename VECT::iterator it(vect.find(KEY(1)));

        REQUIRE CHECK(it != vect.end());

        CHECK_EQUAL(KEY(1), iter::key<VECT>(it));
        CHECK_EQUAL(vect[KEY(1)], iter::value<VECT>(it));
    }


#endif