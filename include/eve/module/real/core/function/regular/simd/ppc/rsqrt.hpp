//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/inf.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> rsqrt_(EVE_SUPPORTS(vmx_), wide<T, N> const &v0) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr(std::same_as<T, float>)
    {
      auto ct = one(eve::as(v0));
      auto es = raw(rsqrt)(v0);
      auto xn = sqr(es);
      auto he = es * half(eve::as(v0));

      xn = vec_nmsub(v0.storage(), xn.storage(), ct.storage());
      xn = fma(xn, he, es);

      if(platform::supports_infinites)
      {
        auto i = inf(eve::as(v0));
        xn     = if_else(is_eqz(v0), i, if_else(v0 == i, eve::zero, xn));
      }

      return xn;
    }
    else
    {
      auto refine = [](auto sw0, auto w0)
      {
        wide<T, N> hest = sw0 * half(eve::as(w0));
        wide<T, N> tmp  = vec_nmsub(w0.storage(), sqr(sw0).storage(), one(eve::as(w0)).storage());
        return fma(tmp, hest, sw0);
      };

      auto est = raw(rsqrt)(v0);
      auto xn  = refine(est, v0);
      xn       = refine(xn, v0);

      if(platform::supports_infinites)
      {
        auto i = inf(eve::as(v0));
        xn     = if_else(is_eqz(v0), i, if_else(v0 == i, eve::zero, xn));
      }

      return xn;
    }
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N>
  rsqrt_(EVE_SUPPORTS(vmx_), raw_type const &, wide<T, N> const &v0) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr(std::is_floating_point_v<T>) { return vec_rsqrte(v0.storage()); }
    else
    {
      return map(raw(rsqrt), v0);
    }
  }
}
