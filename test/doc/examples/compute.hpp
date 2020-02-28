//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
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
