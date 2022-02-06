//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/arithmetic/regular/ldexp.hpp>
#include <eve/module/arithmetic/regular/is_infinite.hpp>
#include <eve/module/arithmetic/regular/round.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<int S, real_value T>
  EVE_FORCEINLINE constexpr T fracscale_(EVE_SUPPORTS(cpu_)
                                         , T const &a0, std::integral_constant<int, S> ) noexcept
  {
    return fracscale(a0, S);
  }

  template<real_value T>
  EVE_FORCEINLINE constexpr T fracscale_(EVE_SUPPORTS(cpu_)
                                  , T const &a0, int scale) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return if_else(is_infinite(a0), zero, a0-ldexp(nearest(ldexp(a0, scale)), -scale));
    }
    else
    {
      return apply_over(fracscale, a0, scale);
    }
  }

  template<int S, decorator D, real_value T>
  EVE_FORCEINLINE constexpr T fracscale_(EVE_SUPPORTS(cpu_)
                                  , D const &
                                  , T const &a0, std::integral_constant<int, S> ) noexcept
  requires(is_one_of<D>(types<toward_zero_type, downward_type, to_nearest_type, upward_type> {}))
  {
    return D()(fracscale)(a0, S);
  }

  template<decorator D, real_value T>
  EVE_FORCEINLINE constexpr T fracscale_(EVE_SUPPORTS(cpu_)
                                  , D const &
                                  , T const &a0, int scale) noexcept
  requires(is_one_of<D>(types<toward_zero_type, downward_type, to_nearest_type, upward_type> {}))
  {
    if constexpr(has_native_abi_v<T>)
    {
      return if_else(is_infinite(a0), zero, a0-ldexp(D()(round)(ldexp(a0, scale)), -scale));
    }
    else
    {
      return apply_over( D()(fracscale), a0, scale);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto fracscale_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, int scale) noexcept
  {
    return mask_op(  cond, eve::fracscale, t, scale);
  }

  //================================================================================================
  // Rounded masked case
  //================================================================================================
  template<conditional_expr C, decorator D, real_value T>
  EVE_FORCEINLINE T fracscale_(EVE_SUPPORTS(cpu_), C const &cond, D const &, T a, int scale) noexcept
  (is_one_of<D>(types<toward_zero_type, downward_type, to_nearest_type, upward_type> {}))
  {
    return mask_op( cond, D()(eve::fracscale), a, scale);
  }
}
