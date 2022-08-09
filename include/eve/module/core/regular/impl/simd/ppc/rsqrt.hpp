//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/half.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/decorator/raw.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/sqr.hpp>
#include <eve/module/core/regular/sub.hpp>

namespace eve::detail
{
template<floating_real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
rsqrt_(EVE_SUPPORTS(vmx_), wide<T, N> const& v0) noexcept requires ppc_abi<abi_t<T, N>>
{
  if constexpr( std::same_as<T, float> )
  {
    auto ct = one(eve::as(v0));
    auto es = raw(rsqrt)(v0);
    auto xn = sqr(es);
    auto he = es * half(eve::as(v0));

    xn = vec_nmsub(v0.storage(), xn.storage(), ct.storage());
    xn = fma(xn, he, es);

    if( platform::supports_infinites )
    {
      auto i = inf(eve::as(v0));
      xn     = if_else(is_eqz(v0), i, if_else(v0 == i, eve::zero, xn));
    }

    return xn;
  }
  else { return map(rsqrt, v0); }
}

template<floating_real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                rsqrt_(EVE_SUPPORTS(vmx_),
                       raw_type const&,
                       wide<T, N> const                &v0) noexcept requires ppc_abi<abi_t<T, N>>
{
  if constexpr( std::is_floating_point_v<T> ) { return vec_rsqrte(v0.storage()); }
  else { return map(raw(rsqrt), v0); }
}
}
