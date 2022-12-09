//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
template<scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_add(wide<T, N>& self, U const& other) noexcept
requires(scalar_value<U> || std::same_as<wide<T, N>, U>) && sve_abi<abi_t<T, N>>
{
  self = svadd_x(sve_true<T>(), self, other);
  return self;
}

template<scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_sub(wide<T, N>& self, U const& other) noexcept
requires(scalar_value<U> || std::same_as<wide<T, N>, U>) && sve_abi<abi_t<T, N>>
{
  self = svsub_x(sve_true<T>(), self, other);
  return self;
}

template<scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_mul(wide<T, N>& self, U const& other) noexcept
requires(scalar_value<U> || std::same_as<wide<T, N>, U>) && sve_abi<abi_t<T, N>>
{
  self = svmul_x(sve_true<T>(), self, other);
  return self;
}

template<scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_div(wide<T, N>& self, U const& other) noexcept
requires(scalar_value<U> || std::same_as<wide<T, N>, U>) && sve_abi<abi_t<T, N>>
{
  if constexpr(sizeof(T) >= 4)  self = svdiv_x(sve_true<T>(), self, other);
  else apply<N::value>([&](auto... I) { (self.set(I, self.get(I) / other.get(I)), ...); });
  return self;
}
}
