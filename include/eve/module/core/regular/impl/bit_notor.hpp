//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/bit_not.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_not.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto bit_notor_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , U const &b) noexcept
  requires bit_compatible_values<T,U>
  {
    return bit_call(bit_notor, a, b);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE auto bit_notor_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , T const &b) noexcept
  {
    if constexpr(floating_value<T>)
    {
      using b_t = as_integer_t<T, unsigned>;
      return bit_cast( b_t(~bit_cast(a,as<b_t>()) | bit_cast(b,as<b_t>())), as(a) );
    }
    else return T(~a | b);
  }

  template<real_simd_value T>
  EVE_FORCEINLINE auto bit_notor_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , T const &b) noexcept
  {
    return bit_or(bit_not(a), b);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto bit_notor_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires bit_compatible_values<U, V>
  {
    return mask_op(  cond, eve::bit_notor, t, f);
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<real_value T0, real_value T1, real_value ...Ts>
  auto bit_notor_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
    requires bit_compatible_values<T0, T1> && (bit_compatible_values<T1, Ts> && ...)
  {
    auto that = bit_or(a1,args...);
    return eve::bit_notor(a0, that);
  }

  template<conditional_expr C, real_value T0, real_value T1, real_value ...Ts>
  auto bit_notor_(EVE_SUPPORTS(cpu_), C const &cond, T0 a0, T1 a1, Ts... args)
    requires bit_compatible_values<T0, T1> && (bit_compatible_values<T1, Ts> && ...)
  {
    auto that = bit_or(a1,args...);
    return mask_op( cond, eve::bit_notor, a0, that);
  }
}
