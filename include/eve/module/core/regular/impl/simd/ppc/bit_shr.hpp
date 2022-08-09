//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/shr.hpp>

#include <type_traits>

namespace eve::detail
{
template<integral_scalar_value T, typename N, integral_scalar_value I>
EVE_FORCEINLINE auto
bit_shr_(EVE_SUPPORTS(vmx_),
         wide<T, N> const& v0,
         wide<I, N> const& v1) noexcept requires ppc_abi<abi_t<T, N>>
{
  using i_t = wide<as_integer_t<T, unsigned>, N>;
  return wide<T, N>(vec_sr(v0.storage(), bit_cast(v1, as<i_t>()).storage()));
}

template<integral_scalar_value T, typename N, integral_scalar_value I>
EVE_FORCEINLINE auto
bit_shr_(EVE_SUPPORTS(vmx_), wide<T, N> const& v0, I v1) noexcept requires ppc_abi<abi_t<T, N>>
{
  using i_t = wide<as_integer_t<T, unsigned>, N>;
  return bit_shr(v0, i_t(v1));
}
}
