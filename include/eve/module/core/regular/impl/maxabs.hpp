//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits/common_value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/max.hpp>

#include <type_traits>

namespace eve::detail
{

  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
  maxabs_(EVE_REQUIRES(cpu_), O const & o, T0 a0, T1 a1, Ts... as) noexcept
  {
    return eve::max[o.drop(saturated2)](eve::abs[o.drop(pedantic2,numeric2)](a0, a1, as...));
  }

  //================================================================================================
  // tuples
  //================================================================================================
  template<kumi::non_empty_product_type Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto maxabs_(EVE_REQUIRES(cpu_), O const & o, Ts tup) noexcept
  {
    return kumi::apply( [&](auto... a) { return eve::maxabs[o](a...); }, tup);
  }
}
