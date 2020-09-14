//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/zero.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> rsqrt_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> const &v0) noexcept
  {
    if constexpr(std::is_same_v<T, float>)
    {
      auto ct = one(eve::as(v0));
      auto es = raw_(rsqrt)(v0);
      auto xn = sqr(es);
      auto he = es * half(eve::as(v0));

      xn = vec_nmsub(v0.storage(), xn.storage(), ct.storage());
      xn = fma(xn, he, es);

      if(platform::supports_infinites)
      {
        auto inf = inf(eve::as(v0));
        xn       = if_else(is_eqz(v0), inf, if_else(v0 == inf, eve::zero, xn));
      }

      return xn;
    }
    else if constexpr(std::is_same_v<T, double>)
    {
      auto refine = [](auto sw0, auto w0) {
        auto hest = sw0 * half(eve::as(w0));
        auto tmp  = vec_nmsub(w0.storage(), sqr(sw0).storage(), one(eve::as(w0)).storage());
        return fma(tmp, hest, sw0);
      };

      auto est = raw_(rsqrt)(v0);
      auto xn  = refine(est, v0);
      xn       = refine(xn, v0);

      if(platform::supports_infinites)
      {
        auto inf = inf(eve::as(v0));
        xn       = if_else(is_eqz(v0), inf, if_else(v0 == inf, eve::zero, xn));
      }

      return xn;
    }
    else
    {
      return map(raw_(rsqrt), v0);
    }
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_>
                  rsqrt_(EVE_SUPPORTS(vmx_), raw_type const &, wide<T, N, ppc_> const &v0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>) { return vec_rsqrte(v0.storage()); }
    else
    {
      return map(raw_(rsqrt), v0);
    }
  }
}

