//
// Created by sam on 02/02/2021.
//

#include <UnitTest++/UnitTest++.h>

#include <libalgebra/libalgebra.h>
#include <libalgebra/alg_types.h>

#include "../time_and_details.h"


using alg::DEG;
using alg::LET;



SUITE(hall_basis) {


    const unsigned test_alphabet_size = 5;
    const unsigned test_max_degree = 4;
    typedef double TestScalarType;
    typedef double TestRationalType;

    typedef alg::lie<TestScalarType, TestRationalType, test_alphabet_size, test_max_degree> LIE;
    typedef alg::lie_basis<TestScalarType, TestRationalType, test_alphabet_size, test_max_degree> LIEBASIS;

    class TestBasis : public alg::hall_basis<test_alphabet_size>
    {
    public:
        typedef double RATIONAL;
        typedef double SCALAR;


        using KEY = typename alg::hall_basis<test_alphabet_size>::KEY;
        const std::vector<std::pair<size_t, size_t>>& get_hall_set_degree_ranges() const
        {
            return hall_set_degree_ranges;
        }

        const std::vector<LET>& get_letters() const
        {
            return letters;
        }

        const std::map<LET, KEY>& get_ltk() const
        {
            return ltk;
        }

    };

    typedef typename TestBasis::KEY KEY;


    TEST(test_basis_created_correct_num_letters) {
        TEST_DETAILS();
        TestBasis basis {};

        CHECK_EQUAL(test_alphabet_size, basis.get_letters().size());
    }

    TEST(test_basis_created_ltk_size) {
        TEST_DETAILS();
        TestBasis basis {};

        CHECK_EQUAL(test_alphabet_size, basis.get_ltk().size());
    }


    TEST(test_growup_functionality) {
        TEST_DETAILS();
        TestBasis basis {};

        CHECK_EQUAL(2, basis.get_hall_set_degree_ranges().size());

        basis.growup(2);

        CHECK_EQUAL(3, basis.get_hall_set_degree_ranges().size());

    }

    TEST(test_degree) {
        TEST_DETAILS();
        TestBasis basis {};

        CHECK_EQUAL(0, basis.degree(0));
        for (LET i=1; i<=test_alphabet_size+1; ++i) {
            CHECK_EQUAL(1, basis.degree(i));
        }
    }


    TEST(test_key_of_letter) {
        TEST_DETAILS();
        TestBasis basis {};

        for (LET i=1; i<=test_alphabet_size; ++i) {
            CHECK_EQUAL(KEY(i), basis.keyofletter(i));
        }

    }

    TEST(test_lparent_of_key_base_letters) {
        TEST_DETAILS();
        TestBasis basis {};

        for (LET i=1; i<=test_alphabet_size; ++i) {
            CHECK_EQUAL(0, basis.lparent(i));
        }

    }

    TEST(test_rparent_of_key_base_letters) {
        TEST_DETAILS();
        TestBasis basis {};

        for (LET i=1; i<=test_alphabet_size; ++i) {
            CHECK_EQUAL(i, basis.rparent(i));
        }

    }

    TEST(test_lparent_of_key_higher_key) {
        TEST_DETAILS();
        TestBasis basis {};

        KEY key = test_alphabet_size + 1;
        CHECK_EQUAL(1, basis.lparent(key));

    }

    TEST(test_rparent_of_key_higher_key) {
        TEST_DETAILS();
        TestBasis basis {};

        KEY key = test_alphabet_size + 1;
        CHECK_EQUAL(2, basis.rparent(key));
    }

    TEST(test_is_letter_for_letters) {
        TEST_DETAILS();
        TestBasis basis {};

        for (LET i=1; i<=test_alphabet_size; ++i) {
            CHECK(basis.letter(i));
        }
    }

    TEST(test_is_letter_non_letter) {
        TEST_DETAILS();
        TestBasis basis {};

        KEY key = test_alphabet_size + 1;
        CHECK(!basis.letter(key));
    }



}