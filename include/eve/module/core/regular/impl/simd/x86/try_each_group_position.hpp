//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/shuffle_l0.hpp>

namespace eve::detail
{

constexpr auto try_each_group_rotate_halfs_pattern = [](int i, int size)
{
  int half = size / 2;
  return (i >= half) * half + (i + 1) % half;
};

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
try_each_group_position_(EVE_SUPPORTS(avx2_), wide<T, N> x, eve::fixed<G>) noexcept
requires std::same_as<abi_t<T, N>, x86_256_> && (G < N::value / 2)
{
  auto x_1 = shuffle_l0(x, lane<G>, try_each_group_rotate_halfs_pattern);

  return kumi::cat(try_each_group_position(x, eve::lane<G * 2>),
                   try_each_group_position(x_1, eve::lane<G * 2>));
}

}
