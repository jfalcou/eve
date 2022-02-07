//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/if_else.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/is_gtz.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/module/core/regular/shr.hpp>
#include <eve/module/core/regular/shl.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<unsigned_scalar_value T, integral_simd_value U>
  EVE_FORCEINLINE  auto rshl_(EVE_SUPPORTS(cpu_)
                            , T const &a0
                            , U const &a1) noexcept
  {
    using w_t = wide < T, cardinal_t<U>>;
    return rshl(w_t(a0), a1);
  }

  template<unsigned_scalar_value T, integral_scalar_value U>
  EVE_FORCEINLINE  auto rshl_(EVE_SUPPORTS(cpu_)
                            , T const &a0
                            , U const &a1) noexcept
  {
    if constexpr(unsigned_value<U>)
    {
      return T(a0 << a1);
    }
    else
    {
#ifndef NDEBUG
      return is_gtz(a1) ? T(a0 << max(zero(eve::as(a1)), a1)) : T(a0 >> max(zero(eve::as(a1)), minus(a1)));
#else
      return is_gtz(a1) ? T(a0 << a1) : T(a0>> minus(a1));
#endif
    }
  }

  template<unsigned_simd_value T, integral_value U>
  EVE_FORCEINLINE  auto rshl_(EVE_SUPPORTS(cpu_)
                            , T const &a0
                            , U const &a1) noexcept
  {
    if constexpr(unsigned_value<U>)
    {
      return T(a0 << a1);
    }
    else if constexpr(scalar_value<U>)
    {
      return (a1 > 0) ? T(shl(a0, a1)) : T(shr(a0, minus(a1)));
    }
    else
    {
      if constexpr(has_native_abi_v<T> && has_native_abi_v<U>)
      {
#ifndef NDEBUG
        return if_else(is_gtz(a1), T(a0 << max(zero(eve::as(a1)), a1)), T(a0 >> max(zero(eve::as(a1)), minus(a1))));
#else
        return if_else(is_gtz(a1), T(a0 << a1), T(a0>> minus(a1)));
#endif
      }
      else
      {
        return apply_over(rshl, a0, a1);
      }
    }
  }
}
