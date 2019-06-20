//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_SIMD_X86_AVX2_RSQRT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_SIMD_X86_AVX2_RSQRT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/fnma.hpp>
#include <eve/constant/inf.hpp>
#include <type_traits>
#include <eve/module/core/function/simd/detail/refine_rsqrt.hpp>


namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> rsqrt_( EVE_SUPPORTS(avx_),
                                        wide<T, N, avx_> const & a00
                                      ) noexcept
  {
    using t_t =  wide<T, N, avx_>; 
    if constexpr( std::is_same_v<T, float>)
    {
      t_t a0 = rsqrt[raw_](a00);
      t_t y = sqr(a0)*a00;
      t_t uh = t_t(rec(8.0f)); 
      a0 = a0*uh*fnma(y, fnma(t_t(3), y, t_t(10)), t_t(15)); //this is Halley cubically convergent iteration
#ifndef BOOST_SIMD_NO_INFINITIES
      a0 = if_else(a00 == Inf(as(a0)), eve::zero_, a0);
#endif
      return if_else(is_eqz(a00), Inf(as(a0)), a0);
    }
    else if constexpr( std::is_same_v<T, double>)
    {
      // To obtain accuracy we need 3 Newton steps or one Halley step followed by one Newton from the raw estimate
      // the second method is a bit faster by half a cycle
      t_t a0 =  rsqrt[raw_](a00);
      t_t y = sqr(a0)*a00;
      t_t uh = t_t(rec(8.0));
      a0 = a0*uh*fnma(y, fnma(t_t(3), y, t_t(10)), t_t(15)); //this is Halley cubically convergent iteration
      a0 = refine_rsqrt(a00, a0); //  one Newton step
#ifndef BOOST_SIMD_NO_INFINITIES
      a0 = if_else(a00 == Inf(as(a00)),eve::zero_, a0);
#endif
      return if_else(is_eqz(a00), Inf(as(a00)), a0);
    }
    else
      return map(eve::rsqrt, a00); 
  }


  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> rsqrt_( EVE_SUPPORTS(avx_)
                                         ,  raw_type const &   
                                         ,  wide<T, N, avx_> const & a0
                                         ) noexcept
  {
    if constexpr( std::is_same_v<T, double>)
      return _mm256_cvtps_pd(_mm_rsqrt_ps(_mm256_cvtpd_ps(a0)));
    //The maximum error for this approximation is 1.5e-12
    else if constexpr( std::is_same_v<T, float>)
    {
      return _mm256_rsqrt_ps( a0 );
    }
    else
      return map(eve::rsqrt, a0); 
  }
  
}

#endif
