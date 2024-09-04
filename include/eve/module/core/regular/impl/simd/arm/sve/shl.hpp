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

namespace eve::detail
{
  template<callable_options O, typename T, typename N, integral_scalar_value S>
  EVE_FORCEINLINE wide<T, N> shl_(EVE_REQUIRES(sve_), O const&, wide<T, N> v, wide<S, N> s) noexcept
    requires (sve_abi<abi_t<T, N>> && sizeof(T) == sizeof(S))
  {
    auto const si = bit_cast(s, as<wide<as_integer_t<T, unsigned>, N>>{});
    return svlsl_x(sve_true<T>(), v, si);
  }

  template<callable_options O, typename T, typename N, integral_scalar_value S>
  EVE_FORCEINLINE wide<T, N> shl_(EVE_REQUIRES(sve_), O const&, wide<T,N> v, S s) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    return svlsl_x(sve_true<T>(), v, wide<as_integer_t<T, unsigned>, N>{s});
  }

  template<callable_options O, typename T, typename N, std::ptrdiff_t S>
  EVE_FORCEINLINE wide<T, N> shl_(EVE_REQUIRES(sve_), O const&, wide<T,N> v, index_t<S>) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    using i_t = as_integer_t<T, unsigned>;
    return svlsl_x(sve_true<T>(), v, i_t{S});
  }
}
