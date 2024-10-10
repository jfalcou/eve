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
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/fnma.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_denormal.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/arch/platform.hpp>

namespace eve::detail
{

  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> rec_(EVE_REQUIRES(vmx_), O const& opts, wide<T, N> w) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(lower) || O::contains(upper))
    {
      return rec.behavior(as<wide<T, N>>{}, cpu_{}, opts, w);
    }
    else if constexpr (O::contains(raw))
    {
      return vec_re(w.storage());
    }
    else if constexpr (O::contains(pedantic))
    {
      if (any(is_denormal(w))) return eve::one(as<T>{}) / w;
      else                      return rec(w);
    }
    else
    {
      auto constexpr fix_inf = [](auto v, auto e) {
        if constexpr (platform::supports_infinites)
          return if_else(is_infinite(v), v & mzero(eve::as{v}), e);
        else
          return e;
      };

      auto constexpr refine_rec = [](auto a0, auto x) {
        // Newton-Raphson: 1/X ~= (1-a0*x)*x + x
        return fma(fnma(x, a0, one(eve::as{a0})), x, x);
      };

      if constexpr (std::is_same_v<double, T>)
      {
        auto estimate = refine_rec(w, rec[raw](w));
        estimate      = refine_rec(w, estimate);
        estimate      = if_else(is_eqz(w), w | inf(eve::as{w}), estimate);
        return fix_inf(w, estimate);
      }
      else if constexpr (std::is_same_v<float, T>)
      {
        auto estimate = refine_rec(w, rec[raw](w));
        estimate      = if_else(is_eqz(w), w | inf(eve::as{w}), estimate);
        return fix_inf(w, estimate);
      }
    }
  }
}
