#include <UnitTest++/UnitTest++.h>
#include "../reporter.h"

int main()
{
    reporter report;
    UnitTest::TestRunner runner(report);

    return runner.RunTestsIf(UnitTest::Test::GetTestList(), NULL, UnitTest::True(), 0);
}