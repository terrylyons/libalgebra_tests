#pragma once
// boost dependencies
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp> // exists
#include <boost/filesystem/fstream.hpp>
// copy, sort, max
#ifdef _MSC_VER
#include <xutility>
#endif
#include <algorithm>
// the unit test framework
#include <UnitTest++/UnitTest++.h>

struct	memfile
{
public:
	char* begin() const;
	char* end() const;
	const char* cbegin() const;
	const char* cend() const;
	size_t size() const;

	// constructor
	memfile(boost::filesystem::path filename, size_t numberOfBytes = 0);
	~memfile();
private:
	boost::filesystem::path const p;
	boost::iostreams::mapped_file_sink file;
	char* b;
	char* e;
	bool readonly;
	bool read_only(bool val);// once readonly always read only
public:
	bool read_only() const;	
};


/// On first call makes a file and copies OBJECT_T& sig (assumes a map type) to it
/// then and on all subsequent calls checks that the entries in sig and the file are identical
/// Used to ensure the integrity of calculations over time as the file is never modified 
/// after first construction
/// SPARSEVECTOR_T is the type of a container that contains POD key value pairs  
///
template <typename SPARSEVECTOR_T, typename PATH_T>
void CHECK_compare_with_file(const SPARSEVECTOR_T& sig, const PATH_T& filepath)
{
	size_t numberOfElements = sig.size();
	typedef typename std::pair< typename SPARSEVECTOR_T::KEY, typename SPARSEVECTOR_T::SCALAR > value_type;
	size_t numberOfBytes = numberOfElements * sizeof(value_type);
	
	memfile sigfile(filepath, numberOfBytes);

	// construct content if not readonly
	if (!sigfile.read_only()) {
		value_type* data_begin = (value_type*)(sigfile.begin());
		value_type* data_end = data_begin + numberOfElements;
		// initialize sigfile
		auto temp = sig.size();
		auto temp2 = data_begin - data_end;
		std::copy(sig.begin(), sig.end(), data_begin);
		std::sort(data_begin, data_end
			, [](const value_type lhs, const value_type rhs) {return lhs.first < rhs.first; });
	}

	// check the read only allocation is the anticipated size
	numberOfBytes = sigfile.size();
	numberOfElements = std::min(numberOfElements, numberOfBytes / sizeof(value_type));
	// create const accessors of correct type to the data in sigfile
	const value_type* data_cbegin = (const value_type*)(sigfile.begin());
	const value_type* data_cend = data_cbegin + numberOfElements;

	// compare the calculated with the stored data
	CHECK_EQUAL(sig.size(), numberOfElements);
	SPARSEVECTOR_T sig_saved_version;
	for (auto a = data_cbegin; a < data_cend; a++)
		sig_saved_version[a->first] = a->second;
	SPARSEVECTOR_T err = sig - sig_saved_version;
	CHECK_EQUAL(SPARSEVECTOR_T(), err);
}
