//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/detail/next_kernel.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/dist.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/signnz.hpp>

#include <type_traits>

namespace eve::detail
{
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
nb_values_(EVE_SUPPORTS(cpu_),
           T const& a,
           U const& b) noexcept requires std::same_as<element_type_t<U>, element_type_t<T>>
{
  return arithmetic_call(nb_values, a, b);
}

template<value T>
EVE_FORCEINLINE auto
nb_values_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept requires has_native_abi_v<T>
{
  using ui_t = as_integer_t<T, unsigned>;
  if constexpr( floating_value<T> )
  {
    auto aa = eve::detail::bitinteger(a);
    auto bb = eve::detail::bitinteger(b);
    auto z  = if_else(
        is_unordered(a, b), eve::valmax(eve::as<ui_t>()), bit_cast(dist(bb, aa), as<ui_t>()));
    return inc[is_ltz(signnz(a) * signnz(b))](z);
  }
  else if constexpr( integral_value<T> ) { return bit_cast(dist(a, b), as<ui_t>()); }
}
}
