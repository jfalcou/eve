//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/logical.hpp>
#include <eve/detail/meta.hpp>

#include <bit>

namespace eve::detail
{
template<real_scalar_value T, typename N>
EVE_FORCEINLINE auto
movemask(logical<wide<T, N>> const& v) noexcept
  requires sve_abi<abi_t<T, N>>
{
  std::uint64_t as_int = std::bit_cast<std::uint64_t>(v);
  constexpr int int_size = N::value > 8 ? N::value / 8 : 1;
  return std::pair{static_cast<detail::make_integer_t<int_size, unsigned>>(as_int), eve::lane<1>};
}
}
