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
  template<callable_options O, integral_scalar_value T, typename N, integral_scalar_value S>
  EVE_FORCEINLINE auto bit_shr_(EVE_REQUIRES(vmx_), O const&, wide<T, N> v, wide<S, N> s) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    return vec_sr(v.storage(), convert(s, as<as_integer_t<T, unsigned>>{}).storage());
  }

  template<callable_options O, integral_scalar_value T, typename N, integral_scalar_value S>
  EVE_FORCEINLINE auto bit_shr_(EVE_REQUIRES(vmx_), O const&, wide<T, N> v, S s) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    using i_t = wide<as_integer_t<T, unsigned>, N>;
    return bit_shr(v, i_t{s});
  }
}
