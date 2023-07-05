//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/is_equal.hpp>
#include <eve/module/core/regular/sqr_abs.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
template<value T>
EVE_FORCEINLINE constexpr as_logical_t<T>
is_unit_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    using ar_t = decltype(eve::sqr_abs(a));
    return almost(is_equal)(sqr_abs(a), one(as<ar_t>()));
  }
  else return apply_over(is_unit, a);
}

template<value T>
EVE_FORCEINLINE constexpr as_logical_t<T>
is_unit_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    using ar_t = decltype(eve::sqr_abs(a));
    return almost(is_equal)(pedantic(abs)(a), one(as<ar_t>())));
  }
  else return apply_over(pedantic(is_unit), a);
}
// -----------------------------------------------------------------------------------------------
// logical masked case
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
is_unit_(EVE_SUPPORTS(cpu_), C const& cond, U const& u) noexcept
{
   return logical_mask_op(cond, is_unit, u);
}
}
