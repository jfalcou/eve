//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_REC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_REC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/function/refine_rec.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/if_else.hpp>
#include <eve/forward.hpp>
#include <eve/tags.hpp>
#include <type_traits>

#ifndef EVE_NO_INFINITIES
#include <eve/function/bitwise_and.hpp>
#include <eve/function/is_inf.hpp>
#include <eve/constant/mzero.hpp>
#endif

#ifndef EVE_NO_DENORMALS
#include <eve/function/bitwise_and.hpp>
#include <eve/function/is_less.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/signmask.hpp>
#endif

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> rec_ ( EVE_SUPPORTS(avx_),
                                          raw_type const& mode,
                                          wide<T, N, avx_> const &a0
                                        ) noexcept
  {
    if constexpr( std::is_same_v<T,double>)
    {
      //The error for this approximation is no more than 1.5.e-12
      return _mm256_cvtps_pd(_mm_rcp_ps( _mm256_cvtpd_ps(a0) ));
    }
    if constexpr( std::is_same_v<T,float>)
    {
      return _mm256_rcp_ps( a0 );
    }
    else
    {
      return rec_(EVE_RETARGET(simd_), mode, a0);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> rec_( EVE_SUPPORTS(avx_), wide<T, N, avx_> const &a0 ) noexcept
  {
    if constexpr( std::is_same_v<T,double> )
    {
      return _mm256_div_pd(One(as(a0)),a0);
    }
    else if constexpr( std::is_same_v<T,float> )
    {
      return _mm256_div_ps(One(as(a0)),a0);
    }
    else
    {
      return rec_(EVE_RETARGET(simd_), a0);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> rec_ ( EVE_SUPPORTS(avx_),
                                          pedantic_type const& mode,
                                          wide<T, N, avx_> const &a0
                                        ) noexcept
  {
    if constexpr( std::is_floating_point_v<T>)
    {
      return rec(a0);
    }
    else
    {
      return rec_(EVE_RETARGET(simd_), mode, a0);
    }
  }
}

#endif
