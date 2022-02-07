//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/nearest.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/ldexp.hpp>
#include <eve/module/core/regular/round.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/skeleton_calls.hpp>

namespace eve::detail
{
  template<int S, real_value T>
  EVE_FORCEINLINE constexpr T roundscale_(EVE_SUPPORTS(cpu_)
                                         , T const &a0, std::integral_constant<int, S> ) noexcept
  {
    return roundscale(a0, S);
  }

  template<real_value T>
  EVE_FORCEINLINE constexpr T roundscale_(EVE_SUPPORTS(cpu_)
                                  , T const &a0, int scale) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return ldexp(nearest(ldexp(a0, scale)), -scale);
    }
    else
    {
      return apply_over(roundscale, a0, scale);
    }
  }

  template<int S, decorator D, real_value T>
  EVE_FORCEINLINE constexpr T roundscale_(EVE_SUPPORTS(cpu_)
                                  , D const &
                                  , T const &a0, std::integral_constant<int, S> ) noexcept
  requires(is_one_of<D>(types<toward_zero_type, downward_type, to_nearest_type, upward_type> {}))
  {
    return D()(roundscale)(a0, S);
  }

  template<decorator D, real_value T>
  EVE_FORCEINLINE constexpr T roundscale_(EVE_SUPPORTS(cpu_)
                                  , D const &
                                  , T const &a0, int scale) noexcept
  requires(is_one_of<D>(types<toward_zero_type, downward_type, to_nearest_type, upward_type> {}))
  {
    if constexpr(has_native_abi_v<T>)
    {
      return ldexp(D()(round)(ldexp(a0, scale)), -scale);
    }
    else
    {
      return apply_over(D()(roundscale), a0, scale);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto roundscale_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, int scale) noexcept
  {
    return mask_op(  cond, eve::roundscale, t, scale);
  }


  //================================================================================================
  // Rounded masked case
  //================================================================================================
  template<conditional_expr C, decorator D, real_value T>
  EVE_FORCEINLINE T roundscale_(EVE_SUPPORTS(cpu_), C const &cond, D const &, T a, int scale) noexcept
  (is_one_of<D>(types<toward_zero_type, downward_type, to_nearest_type, upward_type> {}))
  {
    return mask_op( cond, D()(eve::roundscale), a, scale);
  }
}
