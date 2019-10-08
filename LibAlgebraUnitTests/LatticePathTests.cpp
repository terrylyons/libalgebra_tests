// FastSigsExp1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// the libalgebra framework
#include "libalgebra/alg_types.h"
#include <omp.h>

// the unit test framework
#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <random>
#include <algorithm>

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
SUITE(lattice_paths3)
{
	const int scale = 3;
	const int depth = scale;
	const int width = scale;
	const int STEPS = scale;

	struct categorical_path : alg_types<depth, width, Rational>
	{
		// lib algebra required state
		mutable MAPS maps;
		mutable CBH  cbh;
		// state
		const size_t steps;
		const size_t width;
		const size_t depth;
		std::vector<LIE> increments;


		// accessors
				// dimensions
		size_t Steps() const { return steps; }
		size_t Width() const { return width; }
		size_t Depth() const { return depth; }

		// the path data
		const LIE* begin() const { return &(*increments.begin()); }
		const LIE* end() const { return &(*increments.begin()) + increments.size(); }

		// constructor
		categorical_path() :
			steps(STEPS),
			width(ALPHABET_SIZE), //constant set in alg_types
			depth(DEPTH), //constant set in alg_types
			increments(Steps(), LIE())
		{
			// set up random number generation
				// seeded generator	
			unsigned int seed = (const unsigned int&)0x6d35f0e5b8f6c603;//std::random_device seed; unsigned int seed = seed();
			std::mt19937 generator;
			generator.seed(seed);

			// rng
			std::uniform_int_distribution<LET> distribution(1, ALPHABET_SIZE);

			// create random categorical increments
			for (int i = 0; i < Steps(); ++i)
				increments[i] = LIE(distribution(generator), S(1));
		}
		// helper functions
				/// computes a signature from an iterable sequence of lie elements
		template<class ITERATOR_T>
		TENSOR signature(ITERATOR_T begin, ITERATOR_T end) const
		{
			//https://software.intel.com/en-us/node/583439
			//page 180 of: http://www.openmp.org/mp-documents/OpenMP4.0.0.pdf
			ptrdiff_t N = end - begin;
			TENSOR signature(S(1));
			int count(0);
#pragma omp declare reduction (mymult:TENSOR:omp_out *= exp(maps.l2t(*(begin + omp_in)))) initializer(omp_priv=TENSOR(S(1)))
#pragma omp parallel for reduction(mymult:signature)
			for (ptrdiff_t i = 0; i < N; i++)
				signature *= exp(maps.l2t(*(begin + i)));

			return signature;
		}

		/// computes the logsignature from the signature
		template<class ITERATOR_T>
		LIE logsignature(ITERATOR_T begin, ITERATOR_T end) const
		{
			TENSOR sig = signature(begin, end);
			return maps.t2l(log(sig));
		}
	};

	TEST_FIXTURE(categorical_path, short_lattice_path_high_dimension)
	{
		categorical_path p;
		categorical_path::TENSOR sig = p.signature(p.begin(), p.end());
		categorical_path::LIE logs = p.logsignature(p.begin(), p.end());
		auto u = p.maps.t2l(log(sig));
		//categorical_path::LIE logsig = p.maps.t2l(log(sig));
		std::cout << "Support for the logsignature:" << logs.size()
			<< " and for the signature:" << sig.size()
			<< "\nthe dimension of the ambient lie algebra is:" << categorical_path::LIE::basis.size()
			<< "\nthe dimension of the ambient tensor algebra is:" << categorical_path::TENSOR::basis.size() << "\n";
	}
	// EXPECTED OUTPUT Double 38 seconds Rational 43 seconds: 1965 19173961
}
SUITE(lattice_paths4)
{
	const int scale = 4;
	const int depth = scale;
	const int width = scale;
	const int STEPS = scale;

	struct categorical_path : alg_types<depth, width, Rational>
	{
		// lib algebra required state
		mutable MAPS maps;
		mutable CBH  cbh;
		// state
		const size_t steps;
		const size_t width;
		const size_t depth;
		std::vector<LIE> increments;


		// accessors
				// dimensions
		size_t Steps() const { return steps; }
		size_t Width() const { return width; }
		size_t Depth() const { return depth; }

		// the path data
		const LIE* begin() const { return &(*increments.begin()); }
		const LIE* end() const { return &(*increments.begin()) + increments.size(); }

		// constructor
		categorical_path() :
			steps(STEPS),
			width(ALPHABET_SIZE), //constant set in alg_types
			depth(DEPTH), //constant set in alg_types
			increments(Steps(), LIE())
		{
			// set up random number generation
				// seeded generator	
			unsigned int seed = (const unsigned int&)0x6d35f0e5b8f6c603;//std::random_device seed; unsigned int seed = seed();
			std::mt19937 generator;
			generator.seed(seed);

			// rng
			std::uniform_int_distribution<LET> distribution(1, ALPHABET_SIZE);

			// create random categorical increments
			for (int i = 0; i < Steps(); ++i)
				increments[i] = LIE(distribution(generator), S(1));
		}
		// helper functions
				/// computes a signature from an iterable sequence of lie elements
		template<class ITERATOR_T>
		TENSOR signature(ITERATOR_T begin, ITERATOR_T end) const
		{
			//https://software.intel.com/en-us/node/583439
			//page 180 of: http://www.openmp.org/mp-documents/OpenMP4.0.0.pdf
			ptrdiff_t N = end - begin;
			TENSOR signature(S(1));
			int count(0);
#pragma omp declare reduction (mymult:TENSOR:omp_out *= exp(maps.l2t(*(begin + omp_in)))) initializer(omp_priv=TENSOR(S(1)))
#pragma omp parallel for reduction(mymult:signature)
			for (ptrdiff_t i = 0; i < N; i++)
				signature *= exp(maps.l2t(*(begin + i)));

			return signature;
		}

		/// computes the logsignature from the signature
		template<class ITERATOR_T>
		LIE logsignature(ITERATOR_T begin, ITERATOR_T end) const
		{
			TENSOR sig = signature(begin, end);
			return maps.t2l(log(sig));
		}
	};

	TEST_FIXTURE(categorical_path, short_lattice_path_high_dimension)
	{
		categorical_path p;
		categorical_path::TENSOR sig = p.signature(p.begin(), p.end());
		categorical_path::LIE logs = p.logsignature(p.begin(), p.end());
		auto u = p.maps.t2l(log(sig));
		//categorical_path::LIE logsig = p.maps.t2l(log(sig));
		std::cout << "Support for the logsignature:" << logs.size()
			<< " and for the signature:" << sig.size()
			<< "\nthe dimension of the ambient lie algebra is:" << categorical_path::LIE::basis.size()
			<< "\nthe dimension of the ambient tensor algebra is:" << categorical_path::TENSOR::basis.size() << "\n";
	}
	// EXPECTED OUTPUT Double 38 seconds Rational 43 seconds: 1965 19173961
}
SUITE(lattice_paths5)
{
	const int scale = 5;
	const int depth = scale;
	const int width = scale;
	const int STEPS = scale;

	struct categorical_path : alg_types<depth, width, Rational>
	{
		// lib algebra required state
		mutable MAPS maps;
		mutable CBH  cbh;
		// state
		const size_t steps;
		const size_t width;
		const size_t depth;
		std::vector<LIE> increments;


		// accessors
				// dimensions
		size_t Steps() const { return steps; }
		size_t Width() const { return width; }
		size_t Depth() const { return depth; }

		// the path data
		const LIE* begin() const { return &(*increments.begin()); }
		const LIE* end() const { return &(*increments.begin()) + increments.size(); }

		// constructor
		categorical_path() :
			steps(STEPS),
			width(ALPHABET_SIZE), //constant set in alg_types
			depth(DEPTH), //constant set in alg_types
			increments(Steps(), LIE())
		{
			// set up random number generation
				// seeded generator	
			unsigned int seed = (const unsigned int&)0x6d35f0e5b8f6c603;//std::random_device seed; unsigned int seed = seed();
			std::mt19937 generator;
			generator.seed(seed);

			// rng
			std::uniform_int_distribution<LET> distribution(1, ALPHABET_SIZE);

			// create random categorical increments
			for (int i = 0; i < Steps(); ++i)
				increments[i] = LIE(distribution(generator), S(1));
		}
		// helper functions
				/// computes a signature from an iterable sequence of lie elements
		template<class ITERATOR_T>
		TENSOR signature(ITERATOR_T begin, ITERATOR_T end) const
		{
			//https://software.intel.com/en-us/node/583439
			//page 180 of: http://www.openmp.org/mp-documents/OpenMP4.0.0.pdf
			ptrdiff_t N = end - begin;
			TENSOR signature(S(1));
			int count(0);
#pragma omp declare reduction (mymult:TENSOR:omp_out *= exp(maps.l2t(*(begin + omp_in)))) initializer(omp_priv=TENSOR(S(1)))
#pragma omp parallel for reduction(mymult:signature)
			for (ptrdiff_t i = 0; i < N; i++)
				signature *= exp(maps.l2t(*(begin + i)));

			return signature;
		}

		/// computes the logsignature from the signature
		template<class ITERATOR_T>
		LIE logsignature(ITERATOR_T begin, ITERATOR_T end) const
		{
			TENSOR sig = signature(begin, end);
			return maps.t2l(log(sig));
		}
	};

	TEST_FIXTURE(categorical_path, short_lattice_path_high_dimension)
	{
		categorical_path p;
		categorical_path::TENSOR sig = p.signature(p.begin(), p.end());
		categorical_path::LIE logs = p.logsignature(p.begin(), p.end());
		auto u = p.maps.t2l(log(sig));
		//categorical_path::LIE logsig = p.maps.t2l(log(sig));
		std::cout << "Support for the logsignature:" << logs.size()
			<< " and for the signature:" << sig.size()
			<< "\nthe dimension of the ambient lie algebra is:" << categorical_path::LIE::basis.size()
			<< "\nthe dimension of the ambient tensor algebra is:" << categorical_path::TENSOR::basis.size() << "\n";
	}
	// EXPECTED OUTPUT Double 38 seconds Rational 43 seconds: 1965 19173961
}
SUITE(lattice_paths6)
{
	const int scale = 6;
	const int depth = scale;
	const int width = scale;
	const int STEPS = scale;

	struct categorical_path : alg_types<depth, width, Rational>
	{
		// lib algebra required state
		mutable MAPS maps;
		mutable CBH  cbh;
		// state
		const size_t steps;
		const size_t width;
		const size_t depth;
		std::vector<LIE> increments;


		// accessors
				// dimensions
		size_t Steps() const { return steps; }
		size_t Width() const { return width; }
		size_t Depth() const { return depth; }

		// the path data
		const LIE* begin() const { return &(*increments.begin()); }
		const LIE* end() const { return &(*increments.begin()) + increments.size(); }

		// constructor
		categorical_path() :
			steps(STEPS),
			width(ALPHABET_SIZE), //constant set in alg_types
			depth(DEPTH), //constant set in alg_types
			increments(Steps(), LIE())
		{
			// set up random number generation
				// seeded generator	
			unsigned int seed = (const unsigned int&)0x6d35f0e5b8f6c603;//std::random_device seed; unsigned int seed = seed();
			std::mt19937 generator;
			generator.seed(seed);

			// rng
			std::uniform_int_distribution<LET> distribution(1, ALPHABET_SIZE);

			// create random categorical increments
			for (int i = 0; i < Steps(); ++i)
				increments[i] = LIE(distribution(generator), S(1));
		}
		// helper functions
				/// computes a signature from an iterable sequence of lie elements
		template<class ITERATOR_T>
		TENSOR signature(ITERATOR_T begin, ITERATOR_T end) const
		{
			//https://software.intel.com/en-us/node/583439
			//page 180 of: http://www.openmp.org/mp-documents/OpenMP4.0.0.pdf
			ptrdiff_t N = end - begin;
			TENSOR signature(S(1));
			int count(0);
#pragma omp declare reduction (mymult:TENSOR:omp_out *= exp(maps.l2t(*(begin + omp_in)))) initializer(omp_priv=TENSOR(S(1)))
#pragma omp parallel for reduction(mymult:signature)
			for (ptrdiff_t i = 0; i < N; i++)
				signature *= exp(maps.l2t(*(begin + i)));

			return signature;
		}

		/// computes the logsignature from the signature
		template<class ITERATOR_T>
		LIE logsignature(ITERATOR_T begin, ITERATOR_T end) const
		{
			TENSOR sig = signature(begin, end);
			return maps.t2l(log(sig));
		}
	};

	TEST_FIXTURE(categorical_path, short_lattice_path_high_dimension)
	{
		categorical_path p;
		categorical_path::TENSOR sig = p.signature(p.begin(), p.end());
		categorical_path::LIE logs = p.logsignature(p.begin(), p.end());
		auto u = p.maps.t2l(log(sig));
		//categorical_path::LIE logsig = p.maps.t2l(log(sig));
		std::cout << "Support for the logsignature:" << logs.size()
			<< " and for the signature:" << sig.size()
			<< "\nthe dimension of the ambient lie algebra is:" << categorical_path::LIE::basis.size()
			<< "\nthe dimension of the ambient tensor algebra is:" << categorical_path::TENSOR::basis.size() << "\n";
	}
	// EXPECTED OUTPUT Double 38 seconds Rational 43 seconds: 1965 19173961
}
SUITE(lattice_paths7)
{
	const int scale = 7;
	const int depth = scale;
	const int width = scale;
	const int STEPS = scale;

	struct categorical_path : alg_types<depth, width, Rational>
	{
		// lib algebra required state
		mutable MAPS maps;
		mutable CBH  cbh;
		// state
		const size_t steps;
		const size_t width;
		const size_t depth;
		std::vector<LIE> increments;


		// accessors
				// dimensions
		size_t Steps() const { return steps; }
		size_t Width() const { return width; }
		size_t Depth() const { return depth; }

		// the path data
		const LIE* begin() const { return &(*increments.begin()); }
		const LIE* end() const { return &(*increments.begin()) + increments.size(); }

		// constructor
		categorical_path() :
			steps(STEPS),
			width(ALPHABET_SIZE), //constant set in alg_types
			depth(DEPTH), //constant set in alg_types
			increments(Steps(), LIE())
		{
			// set up random number generation
				// seeded generator	
			unsigned int seed = (const unsigned int&)0x6d35f0e5b8f6c603;//std::random_device seed; unsigned int seed = seed();
			std::mt19937 generator;
			generator.seed(seed);

			// rng
			std::uniform_int_distribution<LET> distribution(1, ALPHABET_SIZE);

			// create random categorical increments
			for (int i = 0; i < Steps(); ++i)
				increments[i] = LIE(distribution(generator), S(1));
		}
		// helper functions
				/// computes a signature from an iterable sequence of lie elements
		template<class ITERATOR_T>
		TENSOR signature(ITERATOR_T begin, ITERATOR_T end) const
		{
            //https://software.intel.com/en-us/node/583439
            //page 180 of: http://www.openmp.org/mp-documents/OpenMP4.0.0.pdf
			ptrdiff_t N = end - begin;
			TENSOR signature(S(1));
			int count(0);
#pragma omp declare reduction (mymult:TENSOR:omp_out *= exp(maps.l2t(*(begin + omp_in)))) initializer(omp_priv=TENSOR(S(1)))
#pragma omp parallel for reduction(mymult:signature)
			for (ptrdiff_t i = 0; i < N; i++)
				signature *= exp(maps.l2t(*(begin+i)));

			return signature;
		}

		/// computes the logsignature from the signature
		template<class ITERATOR_T>
		LIE logsignature(ITERATOR_T begin, ITERATOR_T end) const
		{
			TENSOR sig = signature(begin, end);
			return maps.t2l(log(sig));
		}
	};

TEST_FIXTURE(categorical_path, short_lattice_path_high_dimension)
	{
		categorical_path p;
		categorical_path::TENSOR sig = p.signature(p.begin(), p.end());
		categorical_path::LIE logs = p.logsignature(p.begin(), p.end());
		auto u = p.maps.t2l(log(sig));
		//categorical_path::LIE logsig = p.maps.t2l(log(sig));
		std::cout << "Support for the logsignature:" << logs.size() 
			<< " and for the signature:" << sig.size() 
			<< "\nthe dimension of the ambient lie algebra is:" << categorical_path::LIE::basis.size() 
			<< "\nthe dimension of the ambient tensor algebra is:" << categorical_path::TENSOR::basis.size() << "\n";
	}
	// EXPECTED OUTPUT Double 38 seconds Rational 43 seconds: 1965 19173961
}
SUITE(lattice_paths8)
{
	const int scale = 8;
	const int depth = scale;
	const int width = scale;
	const int STEPS = scale;

	struct categorical_path : alg_types<depth, width, Rational>
	{
		// lib algebra required state
		mutable MAPS maps;
		mutable CBH  cbh;
		// state
		const size_t steps;
		const size_t width;
		const size_t depth;
		std::vector<LIE> increments;


		// accessors
				// dimensions
		size_t Steps() const { return steps; }
		size_t Width() const { return width; }
		size_t Depth() const { return depth; }

		// the path data
		const LIE* begin() const { return &(*increments.begin()); }
		const LIE* end() const { return &(*increments.begin()) + increments.size(); }

		// constructor
		categorical_path() :
			steps(STEPS),
			width(ALPHABET_SIZE), //constant set in alg_types
			depth(DEPTH), //constant set in alg_types
			increments(Steps(), LIE())
		{
			// set up random number generation
				// seeded generator	
			unsigned int seed = (const unsigned int&)0x6d35f0e5b8f6c603;//std::random_device seed; unsigned int seed = seed();
			std::mt19937 generator;
			generator.seed(seed);

			// rng
			std::uniform_int_distribution<LET> distribution(1, ALPHABET_SIZE);

			// create random categorical increments
			for (int i = 0; i < Steps(); ++i)
				increments[i] = LIE(distribution(generator), S(1));
		}
		// helper functions
				/// computes a signature from an iterable sequence of lie elements
		template<class ITERATOR_T>
		TENSOR signature(ITERATOR_T begin, ITERATOR_T end) const
		{
			//https://software.intel.com/en-us/node/583439
			//page 180 of: http://www.openmp.org/mp-documents/OpenMP4.0.0.pdf
			ptrdiff_t N = end - begin;
			TENSOR signature(S(1));
			int count(0);
#pragma omp declare reduction (mymult:TENSOR:omp_out *= exp(maps.l2t(*(begin + omp_in)))) initializer(omp_priv=TENSOR(S(1)))
#pragma omp parallel for reduction(mymult:signature)
			for (ptrdiff_t i = 0; i < N; i++)
				signature *= exp(maps.l2t(*(begin + i)));

			return signature;
		}

		/// computes the logsignature from the signature
		template<class ITERATOR_T>
		LIE logsignature(ITERATOR_T begin, ITERATOR_T end) const
		{
			TENSOR sig = signature(begin, end);
			return maps.t2l(log(sig));
		}
	};

	TEST_FIXTURE(categorical_path, short_lattice_path_high_dimension)
	{
		categorical_path p;
		categorical_path::TENSOR sig = p.signature(p.begin(), p.end());
		categorical_path::LIE logs = p.logsignature(p.begin(), p.end());
		auto u = p.maps.t2l(log(sig));
		//categorical_path::LIE logsig = p.maps.t2l(log(sig));
		std::cout << "Support for the logsignature:" << logs.size()
			<< " and for the signature:" << sig.size()
			<< "\nthe dimension of the ambient lie algebra is:" << categorical_path::LIE::basis.size()
			<< "\nthe dimension of the ambient tensor algebra is:" << categorical_path::TENSOR::basis.size() << "\n";
	}
	// EXPECTED OUTPUT Double 38 seconds Rational 43 seconds: 1965 19173961
}
 //SUITE(lattice_paths9)
 //{
 //	const int scale = 9;
 //	const int depth = scale;
 //	const int width = scale;
 //	const int STEPS = 7;
 //
 //	struct categorical_path : alg_types<depth, width, Rational>
 //	{
 //		// lib algebra required state
 //		mutable MAPS maps;
 //		mutable CBH  cbh;
 //		// state
 //		const size_t steps;
 //		const size_t width;
 //		const size_t depth;
 //		std::vector<LIE> increments;
 //
 //
 //		// accessors
 //				// dimensions
 //		size_t Steps() const { return steps; }
 //		size_t Width() const { return width; }
 //		size_t Depth() const { return depth; }
 //
 //		// the path data
 //		const LIE* begin() const { return &(*increments.begin()); }
 //		const LIE* end() const { return &(*increments.begin()) + increments.size(); }
 //
 //		// constructor
 //		categorical_path() :
 //			steps(STEPS),
 //			width(ALPHABET_SIZE), //constant set in alg_types
 //			depth(DEPTH), //constant set in alg_types
 //			increments(Steps(), LIE())
 //		{
 //			// set up random number generation
 //				// seeded generator	
 //			unsigned int seed = (const unsigned int&)0x6d35f0e5b8f6c603;//std::random_device seed; unsigned int seed = seed();
 //			std::mt19937 generator;
 //			generator.seed(seed);
 //
 //			// rng
 //			std::uniform_int_distribution<LET> distribution(1, ALPHABET_SIZE);
 //
 //			// create random categorical increments
 //			for (int i = 0; i < Steps(); ++i)
 //				increments[i] = LIE(distribution(generator), S(1));
 //		}
 //		// helper functions
 //				/// computes a signature from an iterable sequence of lie elements
 //		template<class ITERATOR_T>
 //		TENSOR signature(ITERATOR_T begin, ITERATOR_T end) const
 //		{
 //			//https://software.intel.com/en-us/node/583439
 //			//page 180 of: http://www.openmp.org/mp-documents/OpenMP4.0.0.pdf
 //			ptrdiff_t N = end - begin;
 //			TENSOR signature(S(1));
 //			int count(0);
 //#pragma omp declare reduction (mymult:TENSOR:omp_out *= exp(maps.l2t(*(begin + omp_in)))) initializer(omp_priv=TENSOR(S(1)))
 //#pragma omp parallel for reduction(mymult:signature)
 //			for (ptrdiff_t i = 0; i < N; i++)
 //				signature *= exp(maps.l2t(*(begin + i)));
 //
 //			return signature;
 //		}
 //
 //		/// computes the logsignature from the signature
 //		template<class ITERATOR_T>
 //		LIE logsignature(ITERATOR_T begin, ITERATOR_T end) const
 //		{
 //			TENSOR sig = signature(begin, end);
 //			return maps.t2l(log(sig));
 //		}
 //	};
 //
 //	TEST_FIXTURE(categorical_path, short_lattice_path_high_dimension)
 //	{
 //		categorical_path p;
 //		categorical_path::TENSOR sig = p.signature(p.begin(), p.end());
 //		categorical_path::LIE logs = p.logsignature(p.begin(), p.end());
 //		auto u = p.maps.t2l(log(sig));
 //		//categorical_path::LIE logsig = p.maps.t2l(log(sig));
 //		std::cout << "Support for the logsignature:" << logs.size()
 //			<< " and for the signature:" << sig.size()
 //			<< "\nthe dimension of the ambient lie algebra is:" << categorical_path::LIE::basis.size()
 //			<< "\nthe dimension of the ambient tensor algebra is:" << categorical_path::TENSOR::basis.size() << "\n";
 //	}
 //	// EXPECTED OUTPUT Double 38 seconds Rational 43 seconds: 1965 19173961
 //}


//output
//Support for the logsignature : 5 and for the signature : 10
//the dimension of the ambient lie algebra is : 14
//the dimension of the ambient tensor algebra is : 40
//Support for the logsignature : 4 and for the signature : 25
//the dimension of the ambient lie algebra is : 90
//the dimension of the ambient tensor algebra is : 341
//Support for the logsignature : 268 and for the signature : 182
//the dimension of the ambient lie algebra is : 829
//the dimension of the ambient tensor algebra is : 3906
//Support for the logsignature : 156 and for the signature : 189
//the dimension of the ambient lie algebra is : 9695
//the dimension of the ambient tensor algebra is : 55987
//Support for the logsignature : 13521 and for the signature : 2942
//the dimension of the ambient lie algebra is : 141280
//the dimension of the ambient tensor algebra is : 960800
//Support for the logsignature : 11245 and for the signature : 1965
//the dimension of the ambient lie algebra is : 2447592
//the dimension of the ambient tensor algebra is : 19173961
//Success : 6 tests passed.
//	Test time : 33.70 seconds.manol benchmark width 2 1000 steps 50k paths degree 5 - one minute.
 // i
