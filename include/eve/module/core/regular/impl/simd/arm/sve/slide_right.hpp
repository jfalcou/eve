//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
template<scalar_value T, typename N, std::ptrdiff_t Shift>
EVE_FORCEINLINE auto
slide_right_(EVE_SUPPORTS(sve_), wide<T, N> v, index_t<Shift>) noexcept
requires(Shift > 0 && Shift < N::value && sve_abi<abi_t<T, N>>)
{
  constexpr auto i = expected_cardinal_v<T> - Shift;
  return wide<T, N>(svext(eve::zero(as(v)),v,i));
}

template<scalar_value T, typename N, std::ptrdiff_t Shift>
EVE_FORCEINLINE auto
slide_right_(EVE_SUPPORTS(sve_), wide<T, N> v, wide<T, N> w, index_t<Shift> s) noexcept
requires(Shift > 0 && Shift < N::value && sve_abi<abi_t<T, N>>)
{
  if constexpr(N::value == expected_cardinal_v<T>)
  {
    constexpr auto i = N::value - Shift;
    return wide<T, N>(svext(v,w,i));
  }
  else
  {
    return slide_right(eve::combine(v,w),s).slice(upper_);
  }
}

template<scalar_value T, typename N, std::ptrdiff_t Shift>
EVE_FORCEINLINE auto
slide_right_(EVE_SUPPORTS(sve_), logical<wide<T, N>> v, index_t<Shift> s) noexcept
requires(Shift > 0 && Shift < N::value && sve_abi<abi_t<T, N>>)
{
  return to_logical(slide_right(v.mask(),s));
}

template<scalar_value T, typename N, std::ptrdiff_t Shift>
EVE_FORCEINLINE auto
slide_right_(EVE_SUPPORTS(sve_), logical<wide<T, N>> v, logical<wide<T, N>> w, index_t<Shift> s) noexcept
requires(Shift > 0 && Shift < N::value && sve_abi<abi_t<T, N>>)
{
  return to_logical(slide_right(v.mask(),w.mask(),s));
}
}
