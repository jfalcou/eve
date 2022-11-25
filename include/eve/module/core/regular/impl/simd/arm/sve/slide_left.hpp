//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/remove_garbage.hpp>

namespace eve::detail
{
template<scalar_value T, typename N, std::ptrdiff_t Shift>
EVE_FORCEINLINE auto
slide_left_(EVE_SUPPORTS(sve_), wide<T, N> v, index_t<Shift>) noexcept
requires(Shift > 0 && Shift < N::value && sve_abi<abi_t<T, N>>)
{
  return wide<T, N>(svext(remove_garbage(v),eve::zero(as(v)),Shift));
}

template<scalar_value T, typename N, std::ptrdiff_t Shift>
EVE_FORCEINLINE auto
slide_left_(EVE_SUPPORTS(sve_), logical<wide<T, N>> v, index_t<Shift> s) noexcept
requires(Shift > 0 && Shift < N::value && sve_abi<abi_t<T, N>>)
{
  return to_logical(slide_left(v.mask(),s));
}
}
