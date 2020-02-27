#ifndef __COMPUTE_HPP
#define __COMPUTE_HPP

#include <boost/simd/pack.hpp>
#include <boost/simd/arch/common/spec.hpp>

//! [runtime-arch]
void compute(float *a, float *b, float *res, int size, boost::simd::avx2_ const&);
void compute(float *a, float *b, float *res, int size, boost::simd::avx_ const&);
void compute(float *a, float *b, float *res, int size, boost::simd::sse4_2_ const&);
void compute(float *a, float *b, float *res, int size, boost::simd::sse4_1_ const&);
void compute(float *a, float *b, float *res, int size, boost::simd::sse3_ const&);
void compute(float *a, float *b, float *res, int size, boost::simd::sse2_ const&);
void compute(float *a, float *b, float *res, int size, boost::dispatch::cpu_ const&);
//! [runtime-arch]

#endif
