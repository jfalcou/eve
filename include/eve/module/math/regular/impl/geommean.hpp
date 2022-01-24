//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math/regular/pow_abs.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE  auto geommean_(EVE_SUPPORTS(cpu_)
                            , T a
                            , U b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(geommean, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE  T geommean_(EVE_SUPPORTS(cpu_)
                            , T a
                            , T b) noexcept
  requires has_native_abi_v<T>
  {
    return if_else(is_nltz(sign(a)*sign(b)), sqrt(abs(a))*sqrt(abs(b)), allbits);
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, floating_real_value U, floating_real_value V>
  EVE_FORCEINLINE auto geommean_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, eve::geommean, t, f);
  }

  //================================================================================================
  //N parameters
  //================================================================================================

  template<floating_real_value T0, floating_real_value T1,  floating_real_value ...Ts>
  auto geommean_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
  requires floating_value<common_compatible_t<T0, T1, Ts...>>
  {
    using r_t = common_compatible_t<T0, T1, Ts...>;
    using elt_t = element_type_t<r_t>;
    elt_t invn = rec(elt_t(sizeof...(args)+2u));
    r_t that(pow_abs(r_t(a0), invn)*pow_abs(r_t(a1), invn));
    r_t sgn =  sign(r_t(a0))*sign(r_t(a1));
    auto next = [&](auto avg,  auto x){
      sgn *= sign(x);
     return avg*pow_abs(r_t(x), invn);

    };
    ((that = next(that,args)),...);
    return if_else(is_even(sizeof...(args)) && is_ltz(sgn),  eve::allbits, sgn*that);
  }
}
