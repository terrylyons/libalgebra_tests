/* *************************************************************

Copyright 2010 Terry Lyons, Stephen Buckley, Djalil Chafai, 
Greg Gyurkó and Arend Janssen. 

Distributed under the terms of the GNU General Public License, 
Version 3. (See accompanying file License.txt)

************************************************************* */
//  libalgebra-demo.cpp : illustrates the use of libalgebra

#include <iostream>

// MAP can be ordered (default) or unordered (faster but unordered)
// LINK to GMP or MPIR and define ARBITRARY_PRECISION to get rational arithmetic 
//#define UNORDEREDMAP
//#define ARBITRARY_PRECISION
#include "libalgebra/libalgebra.h"
#pragma warning(push)
#pragma warning(disable : 4800 4146)
#ifdef ARBITRARY_PRECISION
#include "addons/gmpwrapper.h"
//#include <gmpxx.h>
typedef mpq_class S;
typedef mpq_class Q;
#else
typedef double S;
typedef double Q;
#endif // ARBITRARY_PRECISION
#pragma warning(pop)

const unsigned DEPTH = 5;
const unsigned ALPHABET_SIZE = 2;

const unsigned DEPTH2 = 4;
const unsigned ALPHABET_SIZE2 = 3;

using namespace std;
using namespace alg;

void LibAlgebraTestLieandCBH();
void LibAlgebraTestCommutativePoly();
void LibAlgebraTestPolyLie();

int main(int argc, char* argv[])
{
	LibAlgebraTestPolyLie();
	LibAlgebraTestCommutativePoly();
	LibAlgebraTestLieandCBH();
	return 0;
}

void LibAlgebraTestPolyLie()
{
	typedef poly_lie<S, Q, ALPHABET_SIZE, DEPTH> POLYLIE;
	//'checks' the keyofletter function via this constructor
	POLYLIE poly11(LET(2), S(1));
	std::cout << poly11 << endl;
	//uses the explicit constructor and then uses the Lie bracket
	POLYLIE poly1(1,1,2);
	POLYLIE poly2(1,2,1);
	POLYLIE poly4(2,1,1);
	cout << poly4 << endl;
	poly4 *= S(3);
	std::cout << poly4 << endl;
	poly4 += poly1;
	POLYLIE poly3;
	poly3 = poly4 * poly2;
	std::cout << poly4 << " * " << poly2 << endl << poly3;
}

void LibAlgebraTestCommutativePoly()
{
	typedef multi_polynomial<S, Q, ALPHABET_SIZE, DEPTH> MULTIPOLY;
	typedef poly<S, Q> MULTIPOLY1;
	MULTIPOLY1 p0(S(7)), p1(1,1), p2(2,3), p3, x(0), y(2), z;
	p3 = p0 + p2 * p1 * p2 + p1 * p2;
	std::cout << "  p0 = " << p0 << "  p1(1,1) = " << p1 << "  p2(2,3) = " << p2 << "  p0 + p2*p1*p2+p1*p2 = " << p3 <<
		" and its degree is " << p3.degree() << std::endl;
	x = p3 * p3;
	std::cout << "  p3 * p3 = " << x << "  and its degree is " << x.degree() << std::endl;
	y = exp(p1);
	z = MULTIPOLY1::diff(p3 * p3, 2);
	std::map<LET, S> coordinate;
	coordinate[1] = S(100);
	std::cout << "  the exp of p1 = " << y << " and its value at coord1 = 100 is " << y.eval(coordinate) << std::endl;
	std::cout << "p3 * p3 derivative in the 2 co-ordinate is " << z << std::endl;
}

LET h(LET in) {
	LET out = in;
	return out + LET(1);
};

void LibAlgebraTestLieandCBH()
{
	typedef free_tensor<S, Q, ALPHABET_SIZE, DEPTH> TENSOR;
	typedef free_tensor<S, Q, ALPHABET_SIZE2, DEPTH2> TENSOR2;
	typedef lie<S, Q, ALPHABET_SIZE, DEPTH> LIE;
	typedef maps<S, Q, ALPHABET_SIZE, DEPTH> MAPS;
	typedef maps<S, Q, ALPHABET_SIZE2, DEPTH2> MAPS2;
	typedef cbh<S, Q, ALPHABET_SIZE, DEPTH> CBH;

	MAPS maps;
	CBH cbh;

	LIE l1(1,1);
	LIE l2(2,3);	

	cout << l1 << " and " << l2 << endl;
	l2 *= (S)4;
	cout << l1 << " and " << l2 << endl;
	l2 *= l1 * l2 + l1;
	l2 = l2*l2;
	l2 += l1;
	cout << l1 << " and " << l2 << endl;
	cout << maps.l2t(l2) << endl;
	cout << LIE::basis << endl;
	l2 = LIE(2, 3);
	TENSOR t1(maps.l2t(l1)), t2(maps.l2t(l2)), t(t1 + t2 + t1*t2 - t2*t1);
	cout << "t: " << t << endl;
	cout << maps.t2l(t) << " L1 norm is " << (maps.t2l(t)).NormL1() << endl;
	cout << maps.t2l(t) << " L1 norm of the second order component is " << (maps.t2l(t)).NormL1(2) << endl;

	cout << "l2t(t2l) test: " << (t == maps.l2t(maps.t2l((t)))) << endl;
	cout << "log(exp) test: "<< (t-log(exp(t))) <<" "<< (t == log(exp(t))) << endl;
	cout << "inverse test1: " << (inverse (exp(-t)) - exp(t)) << " " << (inverse(exp(-t)) == exp(t)) << endl;
	{
		int f(2);
		cout << "inverse test2: " << inverse(exp(t) * TENSOR(S(f))) * (exp(t) * TENSOR(S(f))) - TENSOR(S(1))
			<< " " << ((inverse(exp(t) * TENSOR(S(2))) * (exp(t) * TENSOR(S(2)))) == TENSOR(S(1))) 
			<< endl;
	}
	cout << "reflect test: " << (inverse(exp(t)) - reflect(exp(t))) << " " << (inverse(exp(t)) == reflect(exp(t))) << endl;
	vector<LET> letters;
	letters.push_back(1);
	letters.push_back(2);

	cout << "Basic CBH test : " << cbh.basic(letters) << endl;
	LIE a(1,1);
	LIE b(2,1);
	vector<LIE*> v;
	v.push_back(&a);
	v.push_back(&b);
	cout << "Full CBH test : ";
	cout << (cbh.full(v) == cbh.basic(letters)) << endl;

	v.clear();
	v.push_back(&l1);
	v.push_back(&l2);
	cout << "Replace in CBH test: ";
	cout << (replace(cbh.basic(letters), letters, v) == cbh.full(v)) << endl;

	{
// Compute the coordinate-wise min of two numerical tensors - tricky since the zero values count
		TENSOR tt(t);
		tt += TENSOR(2, 4);
		TENSOR T(t), TT(tt);
		cout << "Compute the coordinate-wise min of two tensors: " << endl;
		cout << t << endl;
		cout << tt << endl;
		cout << (t&tt) << endl;
		cout << (tt&t) << endl;
		cout << (T &= tt) << endl;
		cout << (TT &= t) << endl;

// compute the linear transformation of tensors induced by a map of letters
		MAPS2::t2t H(h);
		tt *= tt +=  TENSOR(TENSOR::SCALAR(7));
		cout << tt << "\n" << H(tt) << endl;
	}
}

//EOF.
