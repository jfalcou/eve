//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_RSQRT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_RSQRT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/zero.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> rsqrt_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> const &v0) noexcept
  {
    if constexpr(std::is_same_v<T, float>)
    {
      auto ct = One(as(v0));
      auto es = raw_(rsqrt)(v0);
      auto xn = sqr(es);
      auto he = es * Half(as(v0));

      xn = vec_nmsub(v0.storage(), xn.storage(), ct.storage());
      xn = fma(xn, he, es);

      if(platform::supports_infinites)
      {
        auto inf = Inf(as(v0));
        xn       = if_else(is_eqz(v0), inf, if_else(v0 == inf, eve::zero_, xn));
      }

      return xn;
    }
    else if constexpr(std::is_same_v<T, double>)
    {
      auto refine = [](auto sw0, auto w0) {
        auto hest = sw0 * Half(as(w0));
        auto tmp  = vec_nmsub(w0.storage(), sqr(sw0).storage(), One(as(w0)).storage());
        return fma(tmp, hest, sw0);
      };

      auto est = raw_(rsqrt)(v0);
      auto xn  = refine(est, v0);
      xn       = refine(xn, v0);

      if(platform::supports_infinites)
      {
        auto inf = Inf(as(v0));
        xn       = if_else(is_eqz(v0), inf, if_else(v0 == inf, eve::zero_, xn));
      }

      return xn;
    }
    else
    {
      return map(raw_(rsqrt), v0);
    }
  }

  template<typename T, typename N>
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

#endif
