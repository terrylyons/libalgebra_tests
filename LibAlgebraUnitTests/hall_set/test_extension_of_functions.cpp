//
// Created by sam on 13/09/2021.
//

#include <UnitTest++/UnitTest++.h>

#include <libalgebra/libalgebra.h>

using namespace alg;


std::string letter_func(LET l)
{
    return std::to_string(l);
}

std::string binary_op(const std::string &l, const std::string &r)
{
    return "[" + l + "," + r + "]";
}


SUITE(hall_set_function_extensions) {


    struct fixture
    {

        typedef hall_basis<5> hall_set_t;
        typedef typename hall_set_t::KEY KEY;

        template <typename Function, typename BinOp, typename Tag>
        using extended_function = hall_set_t::extended_function<Function, BinOp,Tag>;

        hall_set_t hall_set;


        extended_function<decltype(&letter_func), decltype(&binary_op), typename hall_set_t::no_caching_tag>
            non_cached_key2str;

        extended_function<decltype(&letter_func), decltype(&binary_op), typename hall_set_t::lazy_cache_tag<3>>
            lazy_cached_key2str;

        extended_function<decltype(&letter_func), decltype(&binary_op), typename hall_set_t::lookup_table_tag<2>>
            table_cached_key2str;

        extended_function<decltype(&letter_func), decltype(&binary_op), typename hall_set_t::lookup_table_tag<0>>
            lazy_nomax_cached_key2str;

        fixture() : hall_set(),
            non_cached_key2str(letter_func, binary_op, hall_set),
            lazy_cached_key2str(letter_func, binary_op, hall_set),
            table_cached_key2str(letter_func, binary_op, hall_set),
            lazy_nomax_cached_key2str(letter_func, binary_op, hall_set)
        {
            hall_set.growup(5);
        }



    };


    TEST_FIXTURE(fixture, test_letter_to_string) {
        LET l = 1;

        CHECK_EQUAL("1", hall_set.key2string(l));
    }

    TEST_FIXTURE(fixture, test_key_to_string_deg_2) {
        KEY k = 6;
        CHECK_EQUAL("[1,2]", hall_set.key2string(k));
    }

    TEST_FIXTURE(fixture, test_key_to_string_deg_3) {
        KEY k = 16;
        CHECK_EQUAL("[1,[1,2]]", hall_set.key2string(k));
    }

    TEST_FIXTURE(fixture, test_letter_to_string_non_cache) {
        LET l = 1;

        CHECK_EQUAL("1", non_cached_key2str(l));
    }

    TEST_FIXTURE(fixture, test_key_to_string_deg_2_non_cache) {
        KEY k = 6;
        CHECK_EQUAL("[1,2]", non_cached_key2str(k));
    }

    TEST_FIXTURE(fixture, test_key_to_string_deg_3_non_cache) {
        KEY k = 16;
        CHECK_EQUAL("[1,[1,2]]", non_cached_key2str(k));
    }

    TEST_FIXTURE(fixture, test_letter_to_string_lazy_cache) {
        LET l = 1;

        CHECK_EQUAL("1", lazy_cached_key2str(l));
    }

    TEST_FIXTURE(fixture, test_key_to_string_deg_2_lazy_cache) {
        KEY k = 6;
        CHECK_EQUAL("[1,2]", lazy_cached_key2str(k));
    }

    TEST_FIXTURE(fixture, test_key_to_string_deg_3_lazy_cache) {
        KEY k = 16;
        CHECK_EQUAL("[1,[1,2]]", lazy_cached_key2str(k));
    }

    TEST_FIXTURE(fixture, test_letter_to_string_table_cache) {
        LET l = 1;

        CHECK_EQUAL("1", table_cached_key2str(l));
    }

    TEST_FIXTURE(fixture, test_key_to_string_deg_2_table_cache) {
        KEY k = 6;
        CHECK_EQUAL("[1,2]", table_cached_key2str(k));
    }

    TEST_FIXTURE(fixture, test_key_to_string_deg_3_table_cache) {
        KEY k = 16;
        CHECK_EQUAL("[1,[1,2]]", table_cached_key2str(k));
    }

    TEST_FIXTURE(fixture, test_letter_to_string_lazy_nomax_cache) {
        LET l = 1;

        CHECK_EQUAL("1", lazy_nomax_cached_key2str(l));
    }

    TEST_FIXTURE(fixture, test_key_to_string_deg_2_lazy_nomax_cache) {
        KEY k = 6;
        CHECK_EQUAL("[1,2]", lazy_nomax_cached_key2str(k));
    }

    TEST_FIXTURE(fixture, test_key_to_string_deg_3_lazy_nomax_cache) {
        KEY k = 16;
        CHECK_EQUAL("[1,[1,2]]", lazy_nomax_cached_key2str(k));
    }


}

