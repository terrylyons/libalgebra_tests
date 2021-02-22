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

#define TEST_BINARY_NEUTRAL(NAME, OP)                            \
    TEST_FIXTURE(Fixture, NAME ## _neutral_neutral) {            \
        TEST_DETAILS();                                          \
        VECT lhs, rhs, expected;                                 \
                                                                 \
        CHECK_EQUAL(expected, lhs OP rhs);                       \
    }                                                            \
                                                                 \
    TEST_FIXTURE(Fixture, NAME ## _random_neutral) {             \
        TEST_DETAILS();                                          \
        VECT neut, other = rand_vec(), expected(other);          \
                                                                 \
        CHECK_EQUAL(expected, other OP neut);                    \
    }                                                            \
                                                                 \
    TEST_FIXTURE(Fixture, NAME ## _netural_random) {             \
        TEST_DETAILS();                                          \
        VECT neut, other = rand_vec(), expected;                 \
        for (KEY i=0; i<BASIS::dimension; ++i)                   \
            expected[i] = S(0) OP other[i];                      \
                                                                 \
        CHECK_EQUAL(expected, neut OP other);                    \
    }

TEST_BINARY_NEUTRAL(test_addition, +);

TEST_BINARY_NEUTRAL(test_subtraction, -);


#undef TEST_BINARY_NEUTRAL

#define TEST_BINARY_OPERATOR(NAME, OP)                           \
    TEST_FIXTURE(Fixture, NAME ## _random_random) {              \
        TEST_DETAILS();                                          \
        VECT lhs = rand_vec(), rhs = rand_vec(), expected;       \
        for (KEY i=0; i < BASIS::dimension; ++i)                 \
            expected[i] = lhs[i] OP rhs[i];                      \
                                                                 \
        CHECK_EQUAL(expected, lhs OP rhs);                       \
    }

TEST_BINARY_OPERATOR(test_addition, +);

TEST_BINARY_OPERATOR(test_subtraction, -);

#undef TEST_BINARY_OPERATOR

#define TEST_INPLACE_BINARY_NEUTRAL(NAME, OP)                    \
    TEST_FIXTURE(Fixture, NAME ## _neutral_neutral) {            \
        TEST_DETAILS();                                          \
        VECT lhs, rhs, expected;                                 \
        lhs OP rhs;                                              \
        CHECK_EQUAL(expected, lhs);                              \
    }                                                            \
                                                                 \
    TEST_FIXTURE(Fixture, NAME ## _random_neutral) {             \
        TEST_DETAILS();                                          \
        VECT neut, other = rand_vec(), expected(other);          \
        other OP neut;                                           \
                                                                 \
        CHECK_EQUAL(expected, other);                            \
    }                                                            \
                                                                 \
    TEST_FIXTURE(Fixture, NAME ## _netural_random) {             \
        TEST_DETAILS();                                          \
        VECT neut, other = rand_vec(), expected;                 \
        for (KEY i=0; i<BASIS::dimension; ++i)                   \
            expected[i] OP other[i];                             \
                                                                 \
        neut OP other;                                           \
        CHECK_EQUAL(expected, neut);                             \
    }

TEST_INPLACE_BINARY_NEUTRAL(test_inplace_addition, +=);

TEST_INPLACE_BINARY_NEUTRAL(test_inplace_subtraction, -=);

#undef TEST_INPLACE_BINARY_NEUTRAL

#define TEST_INPLACE_BINARY_OPERATOR(NAME, OP)                   \
    TEST_FIXTURE(Fixture, NAME ## _random_random) {              \
        TEST_DETAILS();                                          \
        VECT lhs = rand_vec(), rhs = rand_vec(), expected(lhs);  \
        for (KEY i=0; i < BASIS::dimension; ++i)                 \
            expected[i] OP rhs[i];                               \
                                                                 \
        lhs OP rhs;                                              \
        CHECK_EQUAL(expected, lhs);                              \
    }

TEST_INPLACE_BINARY_OPERATOR(test_inplace_addition, +=);

TEST_INPLACE_BINARY_OPERATOR(test_inplace_subtraction, -=);


#undef TEST_INPLACE_BINARY_OPERATOR


#define TEST_BINARY_OPERATOR_FUNC(NAME, OP, FUNC)                \
    TEST_FIXTURE(Fixture, NAME ## _random_random) {              \
        TEST_DETAILS();                                          \
        VECT lhs = rand_vec(), rhs = rand_vec(), expected;       \
        for (KEY i=0; i < BASIS::dimension; ++i)                 \
            expected[i] = FUNC (lhs[i], rhs[i]);                 \
                                                                 \
        CHECK_EQUAL(expected, lhs OP rhs);                       \
    }

TEST_BINARY_OPERATOR_FUNC(test_coordmin, &, std::min);

TEST_BINARY_OPERATOR_FUNC(test_coordmax, |, std::max);

#undef TEST_BINARY_OPERATOR_FUNC


#define TEST_INPLACE_BINARY_OPERATOR_FUNC(NAME, OP, FUNC)        \
    TEST_FIXTURE(Fixture, NAME ## _random_random) {              \
        TEST_DETAILS();                                          \
        VECT lhs = rand_vec(), rhs = rand_vec(), expected;       \
        for (KEY i=0; i < BASIS::dimension; ++i)                 \
            expected[i] = FUNC (lhs[i], rhs[i]);                 \
                                                                 \
        lhs OP rhs;                                              \
        CHECK_EQUAL(expected, lhs);                              \
    }

TEST_INPLACE_BINARY_OPERATOR_FUNC(test_inplace_coordmin, &=, std::min);

TEST_INPLACE_BINARY_OPERATOR_FUNC(test_inplace_coordmax, |=, std::max);

#undef TEST_INPLACE_BINARY_OPERATOR_FUNC


#define TEST_FUSED_OP(NAME, OP1, OP2, STYPE) \
    TEST_FIXTURE(Fixture, test_ ## NAME ## _vec) { \
        TEST_DETAILS();                             \
        VECT lhs = rand_vec(), rhs = rand_vec(), expected(lhs); \
        STYPE scal = (STYPE) rand_scalar();    \
        for (KEY i=0; i<BASIS::dimension; ++i)     \
            expected[i] OP1 (rhs[i] OP2 scal);     \
                                             \
        lhs. NAME(rhs, scal);                   \
        CHECK_EQUAL(expected, lhs);                         \
    }                                        \
                                             \
    TEST_FIXTURE(Fixture, test_ ## NAME ## _key) { \
        TEST_DETAILS();                      \
        VECT lhs = rand_vec(), expected(lhs);\
        KEY rhs = rand_key();                \
        STYPE scal = (STYPE) rand_scalar();    \
        expected[rhs] OP1 (S(1) OP2 scal);   \
                                             \
        lhs. NAME(rhs, scal);                \
        CHECK_EQUAL(expected, lhs);          \
    }

TEST_FUSED_OP(add_scal_prod, +=, *, S);

TEST_FUSED_OP(sub_scal_prod, -=, *, S);

TEST_FUSED_OP(add_scal_div, +=, /, Q);

TEST_FUSED_OP(sub_scal_div, -=, /, Q);

#undef TEST_FUSED_OP

TEST_FIXTURE (Fixture, test_unary_minus_neutral) {
    TEST_DETAILS();
    VECT neut, expected;

    CHECK_EQUAL(expected, -neut);
}

TEST_FIXTURE (Fixture, test_unary_minus_random) {
    TEST_DETAILS();
    VECT vect = rand_vec(), expected;
    for (KEY i = 0; i < BASIS::dimension; ++i)
        expected[i] = -vect[i];

    CHECK_EQUAL(expected, -vect);
}

TEST_FIXTURE(Fixture, test_unary_minus_plus_original_gives_netural) {
    TEST_DETAILS();
    VECT lhs, rhs(rand_vec()), expected;

    lhs = -rhs;

    CHECK_EQUAL(expected, lhs + rhs);
}

TEST_FIXTURE(Fixture, test_random_original_plus_unary_minus_gives_netural) {
    TEST_DETAILS();
    VECT lhs(rand_vec()), rhs(-lhs), expected;

    CHECK_EQUAL(expected, lhs + rhs);
}

#endif  // ifdef _VECTOR_TYPE

