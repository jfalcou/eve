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
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
reverse_(EVE_SUPPORTS(sve_), wide<T, N> v)  noexcept -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  if constexpr(N::value == 1) return v;
  else if constexpr(N::value == expected_cardinal_v<T>) return svrev(v);
  else return svrev(svext(v,v,N::value));
}

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
reverse_(EVE_SUPPORTS(sve_), logical<wide<T, N>> v)  noexcept -> logical<wide<T, N>>
requires sve_abi<abi_t<T, N>>
{
  if constexpr(N::value == 1) return v;
  else if constexpr(N::value == expected_cardinal_v<T>)
  {
          if constexpr(sizeof(T) == 1)  return svrev_b8(v);
    else  if constexpr(sizeof(T) == 2)  return svrev_b16(v);
    else  if constexpr(sizeof(T) == 4)  return svrev_b32(v);
    else  if constexpr(sizeof(T) == 8)  return svrev_b64(v);
  }
  else
  {
    auto mask = v.mask();
    auto w    = to_logical(wide<T,N>(svext(mask,mask,N::value)));

          if constexpr(sizeof(T) == 1)  return svrev_b8(w);
    else  if constexpr(sizeof(T) == 2)  return svrev_b16(w);
    else  if constexpr(sizeof(T) == 4)  return svrev_b32(w);
    else  if constexpr(sizeof(T) == 8)  return svrev_b64(w);
  }
}
}
