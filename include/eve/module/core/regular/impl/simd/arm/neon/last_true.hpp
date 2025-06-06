//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/top_bits.hpp>
#include <eve/module/core/regular/any.hpp>
#include <eve/module/core/regular/convert.hpp>

namespace eve::detail
{
template<callable_options O, arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE std::optional<std::ptrdiff_t>
                last_true_(EVE_REQUIRES(neon128_),
                          O const& opts,
                          logical<wide<T, N>> const                &v0) noexcept requires std::same_as<abi_t<T, N>, arm_128_>
{
  using C = rbr::result::fetch_t<condition_key, O>;
  auto cond = opts[condition_key];
  if constexpr( C::is_complete && !C::is_inverted ) return std::nullopt;
  // we still have to convert down here, so we can do it before ignore.
  else if constexpr( eve::current_api < eve::asimd && sizeof(T) >= 2 )
  {
    using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
    if constexpr(relative_conditional_expr<C>)
    {
      auto halved = eve::convert(v0, eve::as<eve::logical<half_e_t>> {});
      return eve::last_true[cond](halved);
    }
    else
    {
      return last_true(convert(v0 && expand_mask(cond, as(v0)), as<logical<half_e_t>>{}));
    }
  }
  else return last_true.behavior(cpu_{}, opts, v0);
}
}
