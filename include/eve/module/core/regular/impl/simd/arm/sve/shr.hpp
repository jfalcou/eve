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
  EVE_FORCEINLINE wide<T, N> shr_(EVE_REQUIRES(sve_), O const&, wide<T, N> w, wide<S, N> s) noexcept
    requires (sve_abi<abi_t<T, N>> && sizeof(T) == sizeof(S))
  {
    auto const si = convert(s, as<as_integer_t<T, unsigned>>{});

    if constexpr (std::is_signed_v<T>) return svasr_x(sve_true<T>(), w, si);
    else                               return svlsr_x(sve_true<T>(), w, si);
  }

  template<callable_options O, typename T, typename N, integral_scalar_value S>
  EVE_FORCEINLINE wide<T, N> shr_(EVE_REQUIRES(sve_), O const&, wide<T,N> w, S s) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    auto const si = wide<as_integer_t<T, unsigned>, N>{s};

    if constexpr (std::is_signed_v<T>) return svasr_x(sve_true<T>(), w, si);
    else                               return svlsr_x(sve_true<T>(), w, si);
  }

  template<callable_options O, typename T, typename N, std::ptrdiff_t S>
  EVE_FORCEINLINE wide<T, N> shr_(EVE_REQUIRES(sve_), O const&, wide<T,N> w, index_t<S>) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    auto const si = as_integer_t<T, unsigned>{S};

    if constexpr (std::is_signed_v<T>) return svasr_x(sve_true<T>(), w, si);
    else                               return svlsr_x(sve_true<T>(), w, si);
  }
}
