//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/converter.hpp>

namespace eve::detail
{
  template<real_value T, real_value U, real_value V>
  EVE_FORCEINLINE auto fma_(EVE_SUPPORTS(cpu_), T const &a, U const &b, V const &c) noexcept
      requires compatible_values<T, U> &&compatible_values<T, V>
  {
    return arithmetic_call(fma, a, b, c);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE T fma_(EVE_SUPPORTS(cpu_), T const &a, T const &b, T const &c) noexcept
  {
    if constexpr( std::is_same_v<T, float> )
    {
#ifdef FP_FAST_FMAF
      return std::fma(a, b, c);
#else
      return float32(float64(a)*float64(b)+float64(c));
#endif
    }
    else if( std::is_same_v<T, double> )
    {
#ifdef FP_FAST_FMA
      return std::fma(a, b, c);
#else
      return a * b + c;
#endif
    }
    return a * b + c;
  }

  template<real_simd_value T>
  EVE_FORCEINLINE T fma_(EVE_SUPPORTS(cpu_), T const &a, T const &b, T const &c) noexcept
  requires has_native_abi_v<T>
  {
    return a * b + c; // fallback never taken if proper intrinsics are at hand
  }
}
//   template < typename T > inline bool has_accurate_fma(eve::as_<T> const &){
//     if constexpr(std::is_same_v<T, double >) return FP_FAST_FMA == 1;
//     else if  constexpr(std::is_same_v<T, float >) return FP_FAST_FMAF == 1;
//     else return FP_FAST_FMAL == 1;
//   };
