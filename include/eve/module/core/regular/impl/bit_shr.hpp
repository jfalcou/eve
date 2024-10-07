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
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/shr.hpp>
#include <eve/traits/as_integer.hpp>

#include <type_traits>

namespace eve::detail
{
  template<callable_options O, conditional_expr C, typename T, std::ptrdiff_t S>
  EVE_FORCEINLINE constexpr auto bit_shr_(EVE_REQUIRES(cpu_), C const& cx, O const&, T a, index_t<S>) noexcept
  {
    return bit_shr(a, if_else(cx, T{S}, zero));
  }

  template<callable_options O, conditional_expr C, typename T, typename U>
  EVE_FORCEINLINE constexpr auto bit_shr_(EVE_REQUIRES(cpu_), C const& cx, O const&, T a, U s) noexcept
  {
    return bit_shr(a, if_else(cx, s, zero));
  }

  template<callable_options O, typename T, typename U>
  EVE_FORCEINLINE constexpr as_wide_as_t<T, U> bit_shr_(EVE_REQUIRES(cpu_), O const&, T const& a, U const& b) noexcept
  {
    using u_t = eve::as_integer_t<T, unsigned>;
    if constexpr (scalar_value<U>)
    {
           if constexpr (scalar_value<T>) return static_cast<T>(u_t(a) >> ptrdiff_t(b));
      else if constexpr (simd_value<T>)   return bit_cast(bit_cast(a, as<u_t>()) >> ptrdiff_t(b), as(a));
    }
    else // U wide
    {
      if constexpr (scalar_value<T>)
      {
        using w_t = as_wide_as_t<T, U>;
        return bit_shr(w_t(a), b);
      }
      else if constexpr (simd_value<T>)
      {
        return map_pt(as<T>{}, bit_shr, a, b);
      }
    }
  }

  template<callable_options O, typename T, ptrdiff_t V>
  EVE_FORCEINLINE constexpr T bit_shr_(EVE_REQUIRES(cpu_), O const&, T const& a, index_t<V> b) noexcept
  {
    using u_t = eve::as_integer_t<T, unsigned>;
    if constexpr (scalar_value<T>) return static_cast<T>(u_t(a) >> b);
    else                           return bit_cast(bit_cast(a, as<u_t>()) >> b, as(a));
  }
}
