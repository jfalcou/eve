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
#include <eve/module/core/constant/maxflint.hpp>
#include <eve/module/core/constant/true.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/regular/frac.hpp>
#include <eve/module/core/regular/is_nez.hpp>

namespace eve::detail
{
template<ordered_value T>
EVE_FORCEINLINE constexpr auto
is_not_flint_(EVE_SUPPORTS(cpu_), pedantic_type const&, T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    using u_t =  underlying_type_t<T>;
    if constexpr( integral_value<u_t> ) return true_(eve::as<T>());
    else if constexpr( floating_value<u_t> ) return is_nez(frac(a)) || (a > eve::maxflint(eve::as<T>()));
  }
  else return apply_over(pedantic(is_not_flint), a);
}
}
