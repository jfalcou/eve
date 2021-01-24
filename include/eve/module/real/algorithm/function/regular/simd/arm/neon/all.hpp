//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(neon128_), logical<wide<T, N, arm_64_>> const &v0) noexcept
  {
    if constexpr( N::value == 1 )
    {
      return v0.get(0);
    }
    else
    {
      using wide_u32 = wide<std::uint32_t, fixed<2>, arm_64_>;
      auto as_uint32 = eve::bit_cast(v0, eve::as_<eve::logical<wide_u32>>{});

      auto m = as_uint32.bits();

      if constexpr ( sizeof( eve::element_type_t<T> ) >= 4 )
      {
        m = vreinterpret_u32_u64(vpaddl_u32(m));
        uint32_t top = vget_lane_u32(m, 1);

        return static_cast<bool>(top);
      }
      else
      {
        m = vmvn_u32(m);
        m = vorr_u32(m, vrev64_u32(m));
        uint32_t top = vget_lane_u32(m, 1);

        return top == 0;
      }
    }
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(neon128_),
                            logical<wide<T, N, arm_128_>> const &v0) noexcept
  {
    auto [l, h] = v0.slice();
    return all(l && h);
  }
}
