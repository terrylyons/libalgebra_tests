// FastSigsExp1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// the libalgebra framework
#include "libalgebra/alg_types.h"

// the unit test framework
#include <UnitTest++/UnitTest++.h>
#include <iostream>

// simple framework for using lib-algebra
template <unsigned DEPTH, unsigned ALPHABET_SIZE, enum coefficient_t scalar_t>
struct alg_framework : alg_types<DEPTH, ALPHABET_SIZE, scalar_t>
{
	// static tensor class shape 
	using alg_types<DEPTH, ALPHABET_SIZE, scalar_t>::DEPTH;
	using alg_types<DEPTH, ALPHABET_SIZE, scalar_t>::ALPHABET_SIZE;
	// lib algebra required state
	mutable typename alg_types<DEPTH, ALPHABET_SIZE, scalar_t>::MAPS maps;
	mutable typename alg_types<DEPTH, ALPHABET_SIZE, scalar_t>::CBH  cbh;
	// constructor
	alg_framework() {}
};

SUITE(hallset)
{
	const unsigned sc1 = 7;
	typedef alg_framework<sc1, sc1, Rational> SETUP;
	TEST_FIXTURE(SETUP, hall_set44)
	{
		typedef typename std::pair< alg::LET, alg::LET > PARENTS;
		const std::vector<PARENTS>& hall_set = LIE::basis.hall_set;
		const auto& degrees = LIE::basis.degrees;
		const auto& reverse_map = LIE::basis.reverse_map;

		// check it is a hall set https://www.encyclopediaofmath.org/index.php/Hall_set
	
		// contains A
		for (size_t i = 1; i <= ALPHABET_SIZE; ++i)
			CHECK((std::pair<LET, LET>(0, i) == hall_set[i]));

		// order property
		for (const auto& k : hall_set)
			if (k != PARENTS(0, 0))
				CHECK(k.first < k.second);

		// father in-law property
		for (const auto& k : hall_set)
			CHECK(k.first >= hall_set[k.second].first);

		// degrees bounded
		for (LET i = 1; i < hall_set.size(); ++i)
			CHECK(degrees[i] < ALPHABET_SIZE + 1);

		// degrees bounded II
		for (LET i = 1; i < hall_set.size(); ++i)
			CHECK(degrees[hall_set[i].first] + degrees[hall_set[i].second] == degrees[i] && degrees[i] < DEPTH + 1);
		for (LET i = 0; i < 1; ++i)
			CHECK(degrees[i] == 0);
		for (LET i = 1; i < ALPHABET_SIZE + 1; ++i)
			CHECK( degrees[i] == 1);

		// If and only if
		for (LET i = 1; i < hall_set.size(); ++i)
		{
			auto parents = *(hall_set.begin() + i);
			typename std::map<PARENTS, LET>::const_iterator it;
			it = reverse_map.find(parents);
			CHECK(it != reverse_map.end());
		}

		// COMPUTATIONALLY HEAVY
		for (LET i = 1; i < hall_set.size(); ++i)
			for (LET j = i+1; j < hall_set.size(); ++j)
		{
				if (i < hall_set[j].first) {
					PARENTS parents = PARENTS(i, j);
					typename std::map<PARENTS, LET>::const_iterator it;
					it = reverse_map.find(parents);
					CHECK(it == reverse_map.end());
				}
		}
	}


	const int scale = 6;
	const int depth = 6;
	const int width = 6;
	const int STEPS = 6;

	//struct categorical_path : alg_types<depth, width, Rational>
	//{
	//	// lib algebra required state
	//	mutable MAPS maps;
	//	mutable CBH  cbh;
	//	// state
	//	const size_t steps;
	//	const size_t width;
	//	const size_t depth;
	//	std::vector<LIE> increments;
	//
	//
	//	// accessors
	//			// dimensions
	//	size_t Steps() const { return steps; }
	//	size_t Width() const { return width; }
	//	size_t Depth() const { return depth; }
	//
	//	// the path data
	//	const LIE* begin() const { return &(*increments.begin()); }
	//	const LIE* end() const { return &(*increments.begin()) + increments.size(); }
	//
	//	// constructor
	//	categorical_path() :
	//		steps(STEPS),
	//		width(ALPHABET_SIZE), //constant set in alg_types
	//		depth(DEPTH), //constant set in alg_types
	//		increments(Steps(), LIE())
	//	{
	//		// set up random number generation
	//			// seeded generator	
	//		unsigned int seed = (const unsigned int&)0x6d35f0e5b8f6c603;//std::random_device seed; unsigned int seed = seed();
	//		std::mt19937 generator;
	//		generator.seed(seed);
	//
	//		// rng
	//		std::uniform_int_distribution<LET> distribution(1, ALPHABET_SIZE);
	//
	//		// create random categorical increments
	//		for (int i = 0; i < Steps(); ++i)
	//			increments[i] = LIE(distribution(generator), S(1));
	//	}
	//	// helper functions
	//			/// computes a signature from an iterable sequence of lie elements
	//	template<class ITERATOR_T>
	//	TENSOR signature(ITERATOR_T begin, ITERATOR_T end) const
	//	{
	//		TENSOR signature(S(1));
	//		for (ITERATOR_T i = begin; i != end; i++)
	//			signature *= exp(maps.l2t(*i));
	//		return signature;
	//	}
	//
	//	/// computes the logsignature from the signature
	//	template<class ITERATOR_T>
	//	LIE logsignature(ITERATOR_T begin, ITERATOR_T end) const
	//	{
	//		TENSOR sig = signature(begin, end);
	//		return maps.t2l(log(sig));
	//	}
	//};
	//TEST_FIXTURE(categorical_path,bug)
	//{
	//	//4: { 1(4) }
	//	//446 : { 1([3, [2, [2, [2, 3]]]]) }
	//
	//	LIE l1(1), l2(2), l3(3), l4(4);
	//	LIE k1(l4);
	//	LIE k2(l3*(l2*(l2*(l2*(l3)))));
	//	LIE ans = k1 * k2;
	//}
	//
	//TEST_FIXTURE(categorical_path, short_lattice_path_high_dimension)
	//{
	//	categorical_path p;
	//	categorical_path::TENSOR sig = p.signature(p.begin(), p.end());
	//	auto u = p.maps.t2l(log(sig));
	//	//categorical_path::LIE logsig = p.maps.t2l(log(sig));
	//
	//	//std::cout << "Support for the logsignature:" << logsig.size() << " and for the signature:" << sig.size() << ", the dimension of the ambient tensor algebra is:" << categorical_path::TENSOR::basis.size() << "\n";
	//}
	// EXPECTED OUTPUT Double 38 seconds Rational 43 seconds: 1965 19173961
}