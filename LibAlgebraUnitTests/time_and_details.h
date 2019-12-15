#pragma once
#include <chrono>

struct timer
{
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> stop;

	timer() :start{ std::chrono::steady_clock::now() }
	{}

	~timer()
	{
		Adaptive();
	}

	void Adaptive()
	{
		stop = std::chrono::steady_clock::now();
		std::chrono::nanoseconds time = stop - start;

		long long ntime;
		if ((ntime = std::chrono::duration_cast<std::chrono::nanoseconds>(time).count())< 10000LL)
		std::cout << "Elapsed time : "
			<< ntime
			<< " ns" << std::endl;
		else if ((ntime = std::chrono::duration_cast<std::chrono::microseconds>(time).count()) < 10000LL)
			std::cout << "Elapsed time : "
			<< ntime
			<< " micros" << std::endl;
		else if ((ntime = std::chrono::duration_cast<std::chrono::milliseconds>(time).count()) < 10000LL)
			std::cout << "Elapsed time : "
			<< ntime
			<< " ms" << std::endl;
		else {
			ntime = std::chrono::duration_cast<std::chrono::seconds>(time).count();
			std::cout << "Elapsed time : "
				<< ntime
				<< " s" << std::endl;
		}
	}

	void NanoSecs()
	{
		stop = std::chrono::steady_clock::now();
		std::cout << "Elapsed time in nanoseconds : "
			<< std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count()
			<< " ns" << std::endl;
	}

	void MicroSecs()
	{
		stop = std::chrono::steady_clock::now();
		std::cout << "Elapsed time in microseconds : "
			<< std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
			<< " µs" << std::endl;
	}

	void MilliSecs()
	{
		stop = std::chrono::steady_clock::now();
		std::cout << "Elapsed time in milliseconds : "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
			<< " ms" << std::endl;
	}

	void Secs()
	{
		stop = std::chrono::steady_clock::now();
		std::cout << "Elapsed time in seconds : "
			<< std::chrono::duration_cast<std::chrono::seconds>(stop - start).count()
			<< " sec";
	}
};

// a macro to identify and time a test to cout
#ifndef TEST_DETAILS
#ifndef SHO_NO
#define TEST_DETAILS() std::cout << "\nFile : " << m_details.filename << "\nLine : " << m_details.lineNumber << "\nSuite : " << m_details.suiteName << "\nTest : " << m_details.testName << std::endl ; timer t;
#else
#define TEST_DETAILS()
#endif
#else
#endif