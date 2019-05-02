//==================================================================================================
/**
  EVE - Expressive Vector Engine 
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_REC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_REC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/tags.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_inf.hpp>
#include <eve/function/refine_rec.hpp>
#include <type_traits>
 
namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // double
  template<typename N>
  EVE_FORCEINLINE wide<double, N, sse_> rec_(EVE_SUPPORTS(sse2_),
                                             raw_type const &
                                             wide<double, N, sse_> const &a0) noexcept
  {
    return _mm_cvtps_pd(_mm_rcp_ps( _mm_cvtpd_ps(a0) ));//The error for this approximation is no more than 1.5.e-12
  }                                             
  
  template<typename N>
  EVE_FORCEINLINE auto rec_(EVE_SUPPORTS(sse2_),
                            wide<double, N, sse_> const &a00) noexcept
  {
    using t_t = wide<double, N, sse_>; 
    t_t a0 = refine_rec(a00, refine_rec(a00,refine_rec(a00, rec[raw_](a00))));
#ifndef BOOST_SIMD_NO_INFINITIES
    a0 = if_else(is_inf(a00),
                 bitwise_and(a00, Mzero<t_t>()),
                 a0
                );
#endif
#ifndef BOOST_SIMD_NO_DENORMALS
    auto is_den = is_less(bs::abs(a00), Smallestposval<t_t>());
    return if_else(is_den,  bitwise_or(bitofsign(a00), Inf<t_t>()), a0);
#else
    auto is_den = is_eqz(a00);
    return if_else(is_den,  bitwise_or(a00, Inf<t_t>()), a0);
#endif
  }
  
  // -----------------------------------------------------------------------------------------------
  // float
  template<typename N>
  EVE_FORCEINLINE wide<float, N, sse_> rec_(EVE_SUPPORTS(sse2_),
                                             raw_type const &
                                             wide<float, N, sse_> const &a0) noexcept
  {
    return _mm_rcp_ps( a0 );
  }                                             

  template<typename N>
  EVE_FORCEINLINE auto rec_(EVE_SUPPORTS(sse2_),
                            wide<double, N, sse_> const &a00) noexcept
  {
    using t_t = wide<double, N, sse_>; 
    t_t a0 =refine_rec(a00,refine_rec(a00, rec[raw_](a00)));
#ifndef BOOST_SIMD_NO_INFINITIES
    a0 = if_else(is_inf(a00),
                 bitwise_and(a00, Mzero<t_t>()),
                 a0
                );
#endif
#ifndef BOOST_SIMD_NO_DENORMALS
    auto is_den = is_less(bs::abs(a00), Smallestposval<t_t>());
    return if_else(is_den,  bitwise_or(bitofsign(a00), Inf<t_t>()), a0);
#else
    auto is_den = is_eqz(a00);
    return if_else(is_den,  bitwise_or(a00, Inf<t_t>()), a0);
#endif
  }   
}



#endif
