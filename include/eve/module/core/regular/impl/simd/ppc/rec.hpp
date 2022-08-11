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
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/mzero.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/decorator/raw.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/fnma.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/refine_rec.hpp>
#include <eve/platform.hpp>

namespace eve::detail
{
template<floating_real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
rec_(EVE_SUPPORTS(vmx_), raw_type const&, wide<T, N> v0) noexcept requires ppc_abi<abi_t<T, N>>
{
  return vec_re(v0.storage());
}

template<floating_real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                rec_(EVE_SUPPORTS(vmx_), wide<T, N> v0) noexcept requires ppc_abi<abi_t<T, N>>
{
  auto constexpr fix_inf = [](auto v, auto e)
  {
    if constexpr( platform::supports_infinites )
      return if_else(is_infinite(v), v & mzero(eve::as(v)), e);
    else return e;
  };

  auto constexpr refine_rec = [](auto a0, auto x)
  {
    // Newton-Raphson: 1/X ~= (1-a0*x)*x + x
    return fma(fnma(x, a0, one(eve::as(a0))), x, x);
  };

  if constexpr( std::is_same_v<double, T> )
  {
    auto estimate = refine_rec(v0, raw(rec)(v0));
    estimate      = refine_rec(v0, estimate);
    estimate      = if_else(is_eqz(v0), v0 | inf(eve::as(v0)), estimate);
    return fix_inf(v0, estimate);
  }
  else if constexpr( std::is_same_v<float, T> )
  {
    auto estimate = refine_rec(v0, raw(rec)(v0));
    estimate      = if_else(is_eqz(v0), v0 | inf(eve::as(v0)), estimate);
    return fix_inf(v0, estimate);
  }
}
}
