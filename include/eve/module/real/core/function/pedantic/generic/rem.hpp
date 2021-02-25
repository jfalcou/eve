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
#include <eve/function/pedantic.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto rem_ ( EVE_SUPPORTS(cpu_)
                            , pedantic_type const&,T const &a, U const &b
                            ) noexcept requires compatible_values<T, U>
  {
    return if_else(is_nez(b), rem(a,b), a);
  }

  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto
  rem_(EVE_SUPPORTS(cpu_), C const &cond, pedantic_type const &, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op( EVE_CURRENT_API{}, cond, pedantic(rem), t, f);
  }
}
