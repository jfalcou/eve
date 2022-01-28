//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/constant/eps.hpp>
#include <eve/module/arithmetic/regular/abs.hpp>
#include <eve/module/arithmetic/regular/is_not_greater.hpp>
#include <eve/module/arithmetic/saturated/next.hpp>
#include <eve/module/arithmetic/saturated/add.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto is_not_greater_(EVE_SUPPORTS(cpu_)
                                , almost_type const &
                                , T const &a
                                , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(almost(is_not_greater), a, b, 3*eps(as(a)));
  }

  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto is_not_greater_(EVE_SUPPORTS(cpu_)
                                , almost_type const &
                                , logical<T> const &a
                                , logical<U> const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(is_not_greater, a, b);
  }

  template<floating_real_value T, floating_real_value U, real_value V>
  EVE_FORCEINLINE auto is_not_greater_(EVE_SUPPORTS(cpu_)
                                , almost_type const &
                                , T const &a
                                , U const &b
                               ,  V const &tol) noexcept
  requires compatible_values<T, U>
  {
    if constexpr(integral_value<V>)
    {
      using c_t = std::conditional_t<scalar_value<T>, U, T>;
      c_t aa(a);
      c_t bb(b);
      return almost(is_not_greater)(aa, bb, tol);
    }
    else return arithmetic_call(almost(is_not_greater), a, b, tol);
  }

  template<floating_real_value T, value V>
  EVE_FORCEINLINE auto is_not_greater_(EVE_SUPPORTS(cpu_)
                                , almost_type const &
                                , T const &a
                                , T const &b
                                , [[maybe_unused]] V const &tol) noexcept
  {
    if constexpr(integral_value<V>)
    {
      if constexpr(simd_value<V> && scalar_value<T>)
      {
        using c_t = as_wide_t<T, cardinal_t<V>>;
        using i_t = as_integer_t<T, unsigned>;
        return almost(is_not_greater)(c_t(a), c_t(b), convert(tol, as<i_t>()));
      }
      else
      {
        return is_not_greater(a, saturated(next)(b, tol));
      }
    }
    else
    {
      return is_not_greater(a, saturated(add)(b, tol*max(eve::abs(a), eve::abs(b))));
    }
  }
}
