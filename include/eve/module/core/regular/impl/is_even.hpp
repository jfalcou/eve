//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/half.hpp>
#include <eve/module/core/constant/mindenormal.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/smallestposval.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_flint.hpp>
#include <eve/module/core/regular/is_not_equal.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
template<real_value T>
EVE_FORCEINLINE constexpr as_logical_t<T>
is_even_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( floating_value<T> )
    {
      auto aisflt = is_flint(a * half(eve::as(a)));
      auto aa     = eve::abs(a);
      if constexpr( eve::platform::supports_denormals )
        return aisflt && (aa != mindenormal(eve::as<T>()));
      else return aisflt && (aa != smallestposval(eve::as<T>()));
    }
    else if constexpr( scalar_value<T> ) return (!(a & one(eve::as(a))));
    else return is_eqz((a & one(eve::as(a))));
  }
  else return apply_over(is_even, a);
}

// -----------------------------------------------------------------------------------------------
// logical masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
is_even_(EVE_SUPPORTS(cpu_), C const& cond, U const& u) noexcept
{
  return logical_mask_op(cond, is_even, u);
}
}
