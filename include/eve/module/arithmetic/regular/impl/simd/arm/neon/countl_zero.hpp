//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<unsigned_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> countl_zero_(EVE_SUPPORTS(neon128_), wide<T, N> a0) noexcept
      requires arm_abi<abi_t<T, N>>
 {
    using r_t = wide<T, N>;
    constexpr auto c = categorize<r_t>();

          if constexpr( c == category::uint32x4 ) return vclzq_u32(a0);
    else  if constexpr( c == category::uint32x2 ) return  vclz_u32(a0);
    else  if constexpr( c == category::uint16x8 ) return vclzq_u16(a0);
    else  if constexpr( c == category::uint16x4 ) return  vclz_u16(a0);
    else  if constexpr( c == category::uint8x16 ) return  vclzq_u8(a0);
    else  if constexpr( c == category::uint8x8  ) return   vclz_u8(a0);
    else                                          return  map(countl_zero, a0);
  }
}
