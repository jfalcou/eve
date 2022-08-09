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

template<real_scalar_value T, typename N, relative_conditional_expr C>
EVE_FORCEINLINE std::optional<std::ptrdiff_t>
                first_true_(EVE_SUPPORTS(neon128_),
                            C const                                  &cond,
                            logical<wide<T, N>> const                &v0) noexcept requires std::same_as<abi_t<T, N>, arm_128_>
{
  if constexpr( C::is_complete && !C::is_inverted ) return std::nullopt;
  // we still have to convert down here, so we can do it before ignore.
  else if constexpr( eve::current_api < eve::asimd && sizeof(T) >= 2 )
  {
    using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
    auto halved    = eve::convert(v0, eve::as<eve::logical<half_e_t>> {});
    return eve::first_true[cond](halved);
  }
  else return first_true_(EVE_RETARGET(cpu_), cond, v0);
}
}
