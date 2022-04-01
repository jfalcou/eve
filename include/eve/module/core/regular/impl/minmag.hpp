//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_not_greater_equal.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/traits/common_compatible.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto minmag_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(minmag, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto minmag_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
  {
    auto aa  = eve::abs(a);
    auto bb  = eve::abs(b);
    if constexpr( simd_value<T> )
    {
      auto tmp = if_else(is_not_greater_equal(aa, bb), b, eve::min(a, b));
      return if_else(is_not_greater_equal(bb, aa), a, tmp);
    }
    else
    {
      return aa < bb ? b : bb < aa ? a : eve::min(a, b);
    }
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto minmag_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, eve::minmag, t, f);
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<decorator D, real_value T0, real_value T1, real_value ...Ts>
  auto minmag_(EVE_SUPPORTS(cpu_), D const &, T0 a0, T1 a1, Ts... args)
  {
    using r_t = common_compatible_t<T0,T1,Ts...>;
    r_t that(D()(minmag)(r_t(a0),r_t(a1)));
    ((that = D()(minmag)(that,r_t(args))),...);
    return that;
  }

  template<real_value T0, real_value T1, real_value ...Ts>
  common_compatible_t<T0,T1,Ts...> minmag_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
  {
    using r_t = common_compatible_t<T0,T1,Ts...>;
    r_t that(minmag(r_t(a0),r_t(a1)));
    ((that = minmag(that,r_t(args))),...);
    return that;
  }

  template<conditional_expr C, real_value T0, real_value T1, real_value ...Ts>
  common_compatible_t<T0,T1,Ts...> minmag_(EVE_SUPPORTS(cpu_), C const & cond,
                                           T0 a0, T1 a1, Ts... args)
  {
   return mask_op(  cond, eve::minmag, a0, args...);
  }

}
