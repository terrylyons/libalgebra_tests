/* *************************************************************

Copyright 2010-2019 Terry Lyons, Stephen Buckley, Djalil Chafai,
Greg Gyurkó and Arend Janssen.

Distributed under the terms of the GNU General Public License,
Version 3. (See accompanying file License.txt)

************************************************************* */
// THIS TEST SUITE IS DERIVED FROM LIBALGEBRA-DEMO.cpp
// BUT EXPLOITS THE MORE UNIFIED SETUP INTERFACE NOW AVAILABLE
//
// BREAKING CHANGE in CBH which now consumes vector<const LIE*> not 
// vector<LIE*> and there is no natural conversion. Change your code.

// libalgebra functionality
#include "libalgebra/alg_types.h"

// std:: dependencies for current tests
#include <iostream>
#include <vector>

// the unit test framework
#include <UnitTest++/UnitTest++.h>

// a debugging tool - SHOW(X) outputs variable name X and its content to a stream (e.g. cout) 
#include "SHOW.h"
const int DEPTH = 10;
const int WIDTH = 2;
typedef alg_types<DEPTH, WIDTH, Rational> framework;

TEST_FIXTURE(framework, big_num)
{
	MAPS maps;
	LIE arg = LIE(1, S(1));// +LIE(2, -2);
	TENSOR expo = exp(maps.l2t(arg));
	std::cout << expo << " expo\n";
	CHECK(true);
}