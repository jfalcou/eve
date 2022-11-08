//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
template<real_value T0, real_value... Ts>
auto
hypot_(EVE_SUPPORTS(cpu_), pedantic_type const&, T0 a0, Ts... args)
{
  using r_t = common_compatible_t<T0, Ts...>;
  if constexpr( has_native_abi_v<r_t> )
  {
    auto e = -maxmag(exponent(r_t(a0)), exponent(r_t(args))...);
    auto f = [&](auto a){return sqr_abs(pedantic(ldexp)(r_t(a), e)); };
    r_t that = add(f(a0), f(args)...);
    auto r = pedantic(ldexp)(sqrt(that), -e);
    if(none(is_nan(r))) return r;
    auto rinf = numeric(maxabs)(a0, args...);
    return if_else(is_infinite(rinf), rinf, r);
  }
  else { return apply_over(pedantic(hypot), r_t(a0), r_t(args)...); }
}
}
