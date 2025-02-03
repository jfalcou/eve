//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
#include <eve/traits/underlying_type.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>

#include <eve/module/core/regular/div.hpp>
#include <eve/module/core/regular/fnma.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_unordered.hpp>

namespace eve::detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr T rem_(EVE_REQUIRES(cpu_), O const& o, T a, T b) noexcept
  {
    if constexpr(integral_value<T>)
    {
      if constexpr(O::contains(downward) ||
                   (( O::contains(upward) || O::contains(to_nearest)) && !(unsigned_value<T>)))
      {
        return fnma(b, eve::div[o](a, b), a);;
      }
      else
      {
        return fnma(b, eve::div(a, b), a);
      }
    }
    else if constexpr(floating_value<T>)
    {
      if constexpr(O::contains(to_nearest))
      {
        return if_else(is_eqz(b) || is_unordered(a, b),
                       if_else(is_eqz(a) || is_infinite(b), a, allbits),
                       fnma(b, eve::div[to_nearest](a, b), a)); // as remainder
      }
      else if constexpr(O::contains(upward) || O::contains(downward))
      {
        return  fnma(b, eve::div[o](a, b), a);
      }
      else
      {
        if constexpr( current_api == neon && simd_value<T> ) return map(rem, a, b);
        else
        {
          return if_else(is_unordered(a, b) || is_infinite(a) || is_eqz(b),
                         allbits,
                         if_else(is_eqz(a), a, fnma(b, div[toward_zero](a, b), a)));
        }
      }
    }
  }

  template<conditional_expr C, typename T, callable_options O>
  EVE_FORCEINLINE T  rem_(EVE_REQUIRES(cpu_), C const& cond, O const & o, T t, T f) noexcept
  requires(integral_value<T>)
  {
    auto g = if_else(cond, f, one);
    return if_else(cond, eve::rem[o.drop(condition_key)](t, g), t);
  }
}
