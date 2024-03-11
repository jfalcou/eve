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
slide_right_(EVE_SUPPORTS(rvv_), logical<wide<T, N>> v, index_t<Shift>) noexcept
requires(Shift > 0 && Shift < N::value && rvv_abi<abi_t<T, N>>)
{
  logical<wide<T, N>> res {0};
  for( size_t id = Shift; id < N::value; ++id )
  {
    auto val = v.get((id + Shift) % N::value);
    res.set(id, val);
  }
  return res;
}
template<scalar_value T, typename N, std::ptrdiff_t Shift>
EVE_FORCEINLINE auto
slide_right_(EVE_SUPPORTS(rvv_),
             logical<wide<T, N>> v,
             logical<wide<T, N>> w,
             index_t<Shift>) noexcept
requires(Shift > 0 && Shift < N::value && rvv_abi<abi_t<T, N>>)
{
  logical<wide<T, N>> res {0};
  for( size_t id = 0; (id) < N::value; ++id )
  {
    if( id < Shift )
    {
      auto val = v.get(N::value - Shift + id);
      res.set(id, val);
    }
    else
    {
      auto val = w.get(id - Shift);
      res.set(id, val);
    }
  }
  return res;
}
}
