//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<value T, value U, value V>
  EVE_FORCEINLINE auto bit_select_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , U const &b
                                  , V const &c) noexcept
  requires bit_compatible_values<T,U> && bit_compatible_values<T,V>
  {
    return bit_call(bit_select, a, b, c);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE auto bit_select_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , T const &b
                                  , T const &c) noexcept
  {
    return bit_or(bit_and(b, a), bit_andnot(c, a));
  }

  template<real_simd_value T>
  EVE_FORCEINLINE auto bit_select_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , T const &b
                                  , T const &c) noexcept
  {
    // fallback never taken if proper intrinsics are at hand
    return  (b & a) | bit_andnot(c, a);
  }
}
