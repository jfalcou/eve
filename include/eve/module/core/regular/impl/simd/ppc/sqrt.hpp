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
#include <eve/module/core/decorator/raw.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/rsqrt.hpp>

#include <type_traits>

namespace eve::detail
{
template<floating_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
sqrt_(EVE_SUPPORTS(vmx_), wide<T, N> const& v0) noexcept requires ppc_abi<abi_t<T, N>>
{
  if constexpr( std::is_floating_point_v<T> )
  {
    if constexpr( current_api == vmx )
    {
      auto that = if_else(v0, v0 * rsqrt(v0), v0);
      if constexpr( platform::supports_invalids )
      {
        return if_else(v0 == inf(eve::as(v0)), v0, that);
      }
      else { return that; }
    }
    else { return vec_sqrt(v0.storage()); }
  }
}

template<floating_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                sqrt_(EVE_SUPPORTS(vmx_),
                      raw_type const&,
                      wide<T, N> const                &v0) noexcept requires ppc_abi<abi_t<T, N>>
{
  if constexpr( std::is_floating_point_v<T> )
  {
    if constexpr( current_api == vmx ) { return if_else(v0, v0 * raw(rsqrt)(v0), eve::zero); }
    else { return vec_sqrt(v0.storage()); }
  }
}
}
