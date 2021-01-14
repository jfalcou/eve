//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/one.hpp>

namespace eve::detail
{
  template<ad_value T>
  EVE_FORCEINLINE constexpr T sqr_(EVE_SUPPORTS(cpu_), T const &u) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return T(sqr(u.val()), 2*u.val()*u.der());
    else
      return apply_over(eve::sqr, u);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, ad_value U>
  EVE_FORCEINLINE auto sqr_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    auto t = mask_op( EVE_CURRENT_API{}, cond, eve::sqr, t);
    return T(mask_op( t.val(), if_else(cond, t.der(), one); //TODO the else case is not taken properly
  }
}
