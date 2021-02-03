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

    TEST_FIXTURE(Fixture, test_neutral_size_0) {
        TEST_DETAILS();
        VECT neut;

        CHECK_EQUAL(0, neut.size());
    }

    TEST_FIXTURE(Fixture, test_unidim_size_1) {
        TEST_DETAILS();
        VECT vect(KEY(1));

        CHECK_EQUAL(1, vect.size());
    }

    TEST_FIXTURE(Fixture, test_full_dim_size_full) {
        TEST_DETAILS();
        VECT vect = rand_vec(S(1), S(5));

        size_t expected = BASIS::dimension;
        CHECK_EQUAL(expected, vect.size());
    }

    TEST_FIXTURE(Fixture, test_neutral_empty) {
        TEST_DETAILS();
        VECT neut;

        CHECK(neut.empty());
    }

    TEST_FIXTURE(Fixture, test_unidim_not_empty) {
        TEST_DETAILS();
        VECT vect(KEY(1));

        CHECK(!vect.empty());
    }

    TEST_FIXTURE(Fixture, test_full_dim_not_empty) {
        TEST_DETAILS();
        VECT vect = rand_vec(S(1), S(5));

        CHECK(!vect.empty());
    }

    TEST_FIXTURE(Fixture, test_clear_gives_neutral) {
        TEST_DETAILS();
        VECT vect = rand_vec(), neut;

        REQUIRE CHECK(vect != neut);

        vect.clear();
        CHECK(vect.empty());
        CHECK_EQUAL(0, vect.size());
        CHECK_EQUAL(neut, vect);
    }

    TEST_FIXTURE(Fixture, test_erase_by_key) {
        TEST_DETAILS();
        VECT vect = rand_vec();
        KEY k(0);

        REQUIRE CHECK(vect[k] != S(0));

        vect.erase(k);
        CHECK_EQUAL(S(0), vect[k]);
    }


#endif