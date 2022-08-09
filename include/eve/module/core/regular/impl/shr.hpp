//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/detail/overload.hpp>

#include <type_traits>

namespace eve::detail
{
template<integral_value T, integral_value U>
EVE_FORCEINLINE auto
shr_(EVE_SUPPORTS(cpu_), T a, U s) noexcept
{
  if constexpr( scalar_value<T> && scalar_value<U> ) return static_cast<T>(a >> s);
  else if constexpr( scalar_value<T> )
  {
    using w_t = as_wide_t<T, cardinal_t<U>>;
    return w_t(a) >> s;
  }
  else return a >> s;
}

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, integral_value T, integral_value U>
EVE_FORCEINLINE auto
shr_(EVE_SUPPORTS(cpu_), C const& cond, T const& a, U const& b) noexcept
{
  return mask_op(cond, shr, a, b);
}

}
