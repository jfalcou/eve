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
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/decorator/roundings.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/div.hpp>
#include <eve/module/core/regular/fnma.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/nearest.hpp>
#include <eve/module/core/regular/next.hpp>
#include <eve/module/core/regular/trunc.hpp>

namespace eve::detail
{

  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr T rem_(EVE_REQUIRES(cpu_), O const& o, T a, T b) noexcept
  {
    if constexpr(integral_value<T>)
    {
      if constexpr(O::contains(downward2) ||
                   (( O::contains(upward2) || O::contains(to_nearest2)) && !(unsigned_value<T>)))
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
      if constexpr(O::contains(to_nearest2))
      {
        return if_else(is_eqz(b) || is_unordered(a, b),
                       if_else(is_eqz(a) || is_infinite(b), a, allbits),
                       fnma(b, eve::div[to_nearest2](a, b), a)); // as remainder
      }
      else if constexpr(O::contains(upward2) || O::contains(downward2))
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
                         if_else(is_eqz(a), a, fnma(b, div[toward_zero2](a, b), a)));
        }
      }
    }
  }
}
