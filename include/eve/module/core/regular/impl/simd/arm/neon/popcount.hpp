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
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<unsigned_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> popcount_(EVE_REQUIRES(neon128_),
                                       O const&,
                                       wide<T, N> v) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N>>();


    else if constexpr( cat == category::uint8x8         ) return vcnt_u8(v);
    else if constexpr( cat == category::uint8x16        ) return vcntq_u8(v);
    else if constexpr( cat == category::uint16x4        )
    {
      auto z =  bit_cast(v, as<wide<std::uint8, fixed < fixed < N>::value*2>>>>());
      auto r = popcount(z);
      return vpaddl_u8(r);
    }
    else if constexpr( cat == category::uint16x8       )
    {
      auto z =  bit_cast(v, as<wide<std::uint8, fixed < fixed < N>::value*2>>>>());
      auto r = popcount(z);
      return vpaddlq_u8(r);
    }
    else return popcount.behavior(popcount, o, v);

  }
}
