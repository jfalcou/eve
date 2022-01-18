//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/rempio2_kernel.hpp>
#include <eve/detail/kumi.hpp>


namespace eve::detail
{
  template<decorator D, floating_value T>
  EVE_FORCEINLINE auto rempio2_(EVE_SUPPORTS(cpu_), D const &, T const &xx) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( std::is_same_v<D, eve::half_circle_type> )
      {
        return rempio2_half_circle(xx);
      }
      if constexpr( std::is_same_v<D, eve::full_circle_type> )
      {
        return rempio2_full_circle(xx);
      }
      else if constexpr( std::is_same_v<D, eve::detail::medium_type> )
      {
        return rempio2_medium(xx);
      }
      else if constexpr( std::is_same_v<D, eve::detail::big_type> )
      {
        return rempio2_big(xx);
      }
      else if constexpr( std::is_same_v<D, eve::regular_type> )
      {
        return rempio2(xx);
      }
    }
    else
      return apply_over3(D()(rempio2), xx);
  }

  template<floating_value T> EVE_FORCEINLINE
  kumi::tuple<T, T, T> rempio2_(EVE_SUPPORTS(cpu_), T const &x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if( eve::all(x <= Rempio2_limit(quarter_circle_type(), as(x))) )
        return {T(0), x, T(0)};
      else if( eve::all(x <= Rempio2_limit(full_circle_type(), as(x))) )
        return full_circle(rempio2)(x);
      else if( eve::all(x <= Rempio2_limit(half_circle_type(), as(x))) )
        return half_circle(rempio2)(x);
      else if( eve::all(x <= Rempio2_limit(medium_type(), as(x))) )
        return medium(rempio2)(x);
      else
        return big(rempio2)(x);
    }
    else
      return apply_over3(rempio2, x);
  }
}
