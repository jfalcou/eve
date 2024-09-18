//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_gtz.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/minus.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename U>
  EVE_FORCEINLINE constexpr auto rshr_(EVE_REQUIRES(cpu_), O const &, T a0, U a1) noexcept
  {
    if constexpr (scalar_value<U> && scalar_value<T>)
    {
      if constexpr (unsigned_value<U>)
      {
        return T{a0 >> a1};
      }
      else
      {
        #ifndef NDEBUG
          return is_gtz(a1) ? T(a0 >> max(zero(eve::as(a1)), a1)) : T(a0 << max(zero(eve::as(a1)), minus(a1)));
        #else
          return is_gtz(a1) ? T(a0 >> a1) : T(a0 << minus(a1));
        #endif
      }
    }
    else if constexpr (scalar_value<T> && simd_value<U>)
    {
      return rshr(wide<T, cardinal_t<U>>{a0}, a1);
    }
    else if constexpr (scalar_value<U> && simd_value<T>)
    {
      if constexpr (unsigned_value<U>)
      {
        return T{a0 >> a1};
      }
      else
      {
        #ifndef NDEBUG
          return is_gtz(a1) ? T(a0 >> max(zero(eve::as(a1)), a1)) : T(a0 << max(zero(eve::as(a1)), minus(a1)));
        #else
          return is_gtz(a1) ? T(a0 >> a1) : T(a0 << minus(a1));
        #endif
      }
    }
    else if constexpr (simd_value<U> && simd_value<T>)
    {
      if constexpr (unsigned_value<U>)
      {
        return T{a0 >> a1};
      }
      else if constexpr (scalar_value<U>)
      {
        return (a1 > 0) ? T(shr(a0, a1)) : T(shl(a0, minus(a1)));
      }
      else
      {
        #ifndef NDEBUG
          return if_else(is_gtz(a1), T(a0 >> max(zero(eve::as(a1)), a1)), T(a0 << max(zero(eve::as(a1)), -a1)));
        #else
          return if_else(is_gtz(a1), T(a0 >> a1), T(a0 << minus(a1)));
        #endif
      }
    }
  }

  template<callable_options O, integral_value T, std::ptrdiff_t S>
  EVE_FORCEINLINE constexpr auto rshr_(EVE_REQUIRES(cpu_), O const &, T v, index_t<S>) noexcept
  {
    if constexpr (S == 0) return v;
    else                  return rshr(v, S);
  }
}
