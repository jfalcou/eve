//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/inf.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/refine_rec.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/forward.hpp>
#include <eve/platform.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N>
  rec_(EVE_SUPPORTS(vmx_), raw_type const&, wide<T, N> const &v0) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    return vec_re(v0.storage());
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> rec_(EVE_SUPPORTS(vmx_), wide<T, N> const &v0) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    auto constexpr fix_inf = [](auto v, auto e)
    {
      if constexpr(platform::supports_infinites)
        return if_else(is_infinite(v), v & mzero(eve::as(v)), e);
      else
        return e;
    };

    if constexpr(std::is_same_v<double, T>)
    {
      auto    estimate  = refine_rec(v0, raw(rec)(v0));
              estimate  = refine_rec(v0, estimate);
              estimate  = if_else(is_eqz(v0), v0 | inf(eve::as(v0)), estimate);
      return  fix_inf(v0,estimate);
    }
    else if constexpr(std::is_same_v<float, T>)
    {
      auto    estimate  = refine_rec(v0, raw(rec)(v0));
              estimate  = if_else(is_eqz(v0), v0 | inf(eve::as(v0)), estimate);
      return  fix_inf(v0,estimate);
    }
  }
}
