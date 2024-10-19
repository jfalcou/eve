//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/ilogb.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto exponent_(EVE_REQUIRES(avx512_), O const& o, wide<T, N> w) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    if  constexpr(O::contains(raw)) return ilogb(w);
    else return exponent.behavior(cpu_{}, o, w);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto exponent_(EVE_REQUIRES(avx512_), C const& mask, O const& o, wide<T, N> w) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    auto const            src = alternative(mask, w, as{w});
    [[maybe_unused]] auto m = expand_mask(mask, as{w}).storage().value;
    constexpr auto        c = categorize<wide<T, N>>();

    if constexpr (C::is_complete) return src;
    else if  constexpr(O::contains(raw)) return ilogb[o](w);
    else return exponent.behavior(cpu_{}, o, w);
  }
}
