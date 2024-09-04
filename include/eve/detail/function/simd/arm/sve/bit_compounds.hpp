//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>

namespace eve::detail
{
template<integral_scalar_value T, typename N, integral_scalar_value U>
EVE_FORCEINLINE auto&
self_shr(wide<T,N>& self, wide<U,N> shift) noexcept
requires (sve_abi<abi_t<T, N>> && sizeof(T) == sizeof(U))
{
  using u_t = typename wide<T,N>::template rebind <as_integer_t<T, unsigned>,N>;

  if constexpr( std::is_signed_v<T> )
  {
    self = svasr_x(sve_true<T>(), self, bit_cast(shift,as<u_t>()));
    return self;
  }
  else
  {
    self = svlsr_x(sve_true<T>(), self, bit_cast(shift,as<u_t>()));
    return self;
  }
}

template<integral_scalar_value T, typename N, integral_scalar_value U>
EVE_FORCEINLINE auto&
self_shr(wide<T,N>& self, U shift) noexcept
requires sve_abi<abi_t<T, N>>
{
  using u_t = typename wide<T,N>::template rebind <as_integer_t<T, unsigned>,N>;

  if constexpr( std::is_signed_v<T> )
  {
    self = svasr_x(sve_true<T>(), self, u_t(shift));
    return self;
  }
  else
  {
    self = svlsr_x(sve_true<T>(), self, u_t(shift));
    return self;
  }
}

template<integral_scalar_value T, typename N, std::ptrdiff_t U>
EVE_FORCEINLINE auto&
self_shr(wide<T,N>& self, index_t<U>  const&) noexcept
requires sve_abi<abi_t<T, N>>
{
  using u_t = as_integer_t<T, unsigned>;
  constexpr u_t shift(U);
  if constexpr( std::is_signed_v<T> )
  {
    self = svasr_x(sve_true<T>(), self, u_t(shift));
    return self;
  }
  else
  {
    self = svlsr_x(sve_true<T>(), self, u_t(shift));
    return self;
  }
}
}
