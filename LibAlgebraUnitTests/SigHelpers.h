#pragma once

		// helper functions
		/// computes a signature from an iterable sequence of lie elements
		template<class ITERATOR_T>
		TENSOR signature(ITERATOR_T begin, ITERATOR_T end) const
		{
			//#undef  _OPENMP
#ifndef _OPENMP 
		 //simple non-parallel form
			TENSOR signature(S(1));
			for (ITERATOR_T i = begin; i != end; i++)
				signature *= exp(maps.l2t(*i));
			return signature;
#else
			ptrdiff_t leaves = end - begin;
			const LIE* in = &(*begin);
			CTreeBufferHelper t(1, leaves);
			ptrdiff_t e = t.end();
			// storage for the intermediate calculations 
			// only requires one element per thread; 
			// the approach here retains all intermediate values 
			// and is wasteful unless required
			std::vector<TENSOR> sigs(e);

#pragma omp parallel for
			for (ptrdiff_t i = 0; i < leaves; i++)
				sigs[i] = exp(maps.l2t(in[i]));

			for (ptrdiff_t j = t.parent(0); j < e; j = t.parent(j))
			{
				ptrdiff_t jj = t.parent(j);
#pragma omp parallel for
				for (ptrdiff_t i = j; i < jj; i++) {
					// use move semantics and avoid a copy?
					sigs[i] = sigs[t.left(i)] * sigs[t.right(i)];
				}
			}
			return *sigs.crbegin();
#endif // _OPENMP
		};

