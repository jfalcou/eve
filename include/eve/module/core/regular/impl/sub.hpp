//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <cfenv>
#include <eve/concept/value.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_mask.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_gez.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/is_lez.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/saturate.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/detail/roundings.hpp>

namespace eve::detail
{
  template<callable_options O, typename T>
  EVE_FORCEINLINE constexpr T sub_(EVE_REQUIRES(cpu_), O const&, T a, T b) noexcept
  {
    if constexpr(floating_value<T> && (O::contains(lower) || O::contains(upper) ))
    {
      using namespace spy::literal;
      if constexpr(enable_roundings)
      {
        return with_rounding<O> (eve::sub, a, b);
      }
      else
      {
       auto [r, e] = eve::two_add(a, -b);
       if constexpr(O::contains(lower))
         return eve::prev[eve::is_ltz(e)](r);
       else
         return eve::next[eve::is_gtz(e)](r);
      }
    }
    if constexpr (O::contains(saturated) && integral_value<T>)
    {
      if constexpr (scalar_value<T>)
      {
        if constexpr (signed_integral_value<T>)
        {
          if constexpr (sizeof(T) >= 4)
          {
            auto test = is_ltz(b);
            auto pos  = min(add(valmax(as(a)), b), a);
            auto neg  = max(add(valmin(as(a)), b), a);
            return sub(if_else(test, pos, neg), b);
          }
          else
          {
            // small scalar signed integral case uses C++ promotion
            auto r = a - b;
            return static_cast<T>(saturate(r, as<T>()));
          }
        }
        else //unsigned
        {
          T r = a - b;
          return static_cast<T>(r & -(r <= a));
        }
      }
      else //simd
      {
        if constexpr (signed_integral_value<T>)
        {
          auto test = is_lez(b);
          auto pos  = min(add(valmax(as(a)), b), a);
          auto neg  = max(add(valmin(as(a)), b), a);
          return sub(if_else(test, pos, neg), b);
        }
        else //unsigned
        {
          T r = a - b;
          return bit_and(r, bit_mask(r <= a));
        }
      }
    }
    else
    {
      if constexpr(signed_integral_scalar_value<T>)
      {
        using u_t = as_integer_t<T, unsigned>;
        return T(u_t(a)+u_t(-b));
      }
      else
      {
        return a-b;
      }
    }
  }

  template<callable_options O, typename T, std::same_as<T>... Ts>
  EVE_FORCEINLINE constexpr T sub_(EVE_REQUIRES(cpu_), O const & o, T r0, T r1, Ts... rs) noexcept
  {
    r0   = sub[o](r0,r1);
    ((r0 = sub[o](r0,rs)),...);
    return r0;
  }
}
