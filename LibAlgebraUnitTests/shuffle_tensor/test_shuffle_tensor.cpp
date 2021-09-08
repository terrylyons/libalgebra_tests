#include <UnitTest++/UnitTest++.h>

#include <libalgebra/libalgebra.h>

SUITE(shuffle_tensor)
{
    TEST(Sanity_Pass)
    {
        CHECK_EQUAL(1, 1);
    }

    TEST(Sanity_Fail)
    {
        CHECK_EQUAL(1, 2);
    }
}