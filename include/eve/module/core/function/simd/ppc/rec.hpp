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
#include <eve/function/refine_rec.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/forward.hpp>
#include <eve/platform.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_>
                  rec_(EVE_SUPPORTS(vmx_), raw_type const&, wide<T, N, ppc_> const &v0) noexcept
  {
    return vec_re(v0.storage());
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> rec_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> const &v0) noexcept
  {
    if constexpr(std::is_same_v<double, T>)
    {
      auto    estimate  = refine_rec(v0, raw(rec)(v0));
              estimate  = refine_rec(v0, estimate);
              estimate  = if_else(is_eqz(v0), bit_or(v0, inf(eve::as(v0))), estimate);
      return  estimate;
    }
    else if constexpr(std::is_same_v<float, T>)
    {
      auto    estimate  = refine_rec(v0, raw(rec)(v0));
              estimate  = if_else(is_eqz(v0), bit_or(v0, inf(eve::as(v0))), estimate);
      return  estimate;
    }
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_>
                  rec_(EVE_SUPPORTS(vmx_), pedantic_type const&, wide<T, N, ppc_> const &v0) noexcept
  {
    auto estimate = rec(v0);

    if constexpr(platform::supports_infinites)
    {
      estimate = if_else(is_infinite(v0), bit_and(v0, mzero(eve::as(v0))), estimate);
    }

    return estimate;
  }
}

