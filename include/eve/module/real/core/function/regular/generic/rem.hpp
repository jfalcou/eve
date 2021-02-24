//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/binarize_not.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/roundings.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto
  rem_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires compatible_values<T, U>
  {
    return fnma(b, toward_zero(div)(a,b), a);
  }

//   template<real_value T, real_value U>
//   EVE_FORCEINLINE auto rem_ ( EVE_SUPPORTS(cpu_)
//                             , pedantic_type const&,T const &a, U const &b
//                             ) noexcept requires compatible_values<T, U>
//   {
//     return if_else(is_nez(b), rem(a,b), a);
//   }

  template<real_value T, real_value U, decorator D>
  EVE_FORCEINLINE auto rem_ ( EVE_SUPPORTS(cpu_), D const& d
                            , T const &a, U const &b
                            ) noexcept
  requires compatible_values<T, U>
  {
    auto tmp =  fnma(b, d(eve::div)(a,b), a);
    if constexpr(floating_value<T> && is_one_of<D>(types<to_nearest_type, toward_zero_type> {}))
    {
      return if_else(is_eqz(tmp), bitofsign(a), tmp);
    }
    else
      return if_else(is_nez(b),tmp, a);
  }


  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto rem_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op( EVE_CURRENT_API{}, cond, eve::rem, t, f);
  }

  template<conditional_expr C, decorator D, real_value U, real_value V>
  EVE_FORCEINLINE auto
  rem_(EVE_SUPPORTS(cpu_), C const &cond, D const &, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op( EVE_CURRENT_API{}, cond, D()(rem), t, f);
  }
}
