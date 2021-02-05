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
#include <eve/conditional.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/convert.hpp>
#include <eve/arch/logical.hpp>

namespace eve::detail
{
  template <typename T, typename N, typename ABI, typename C>
  EVE_FORCEINLINE bool all_arm_impl(logical<wide<T, N, ABI>> const &v0, C const & cond)
  {
         if constexpr ( C::is_complete && !C::is_inverted ) return true;
    else if constexpr ( std::same_as<ABI, arm_128_> )
    {
      if constexpr ( sizeof( T ) >= 2 )
      {
        using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
        auto halved = eve::convert(v0, eve::as_<eve::logical<half_e_t>>{});
        return all_arm_impl(halved, cond);
      }
      else
      {
        auto [l, h] = v0.slice();
        return all_arm_impl(l && h, cond);
      }
    }
    else if constexpr ( N::value == 1 )                     return v0.get(0);
    else if constexpr ( std::same_as<ABI, arm_64_> )
    {
      using u32_2 = wide<std::uint32_t, eve::fixed<2>, arm_64_>;
      auto as_uint32 = eve::bit_cast(v0.bits(), eve::as_<u32_2>{});

      as_uint32 = vpmin_u32(as_uint32, as_uint32);
      std::uint32_t top = vget_lane_u32(as_uint32, 1);

      if constexpr ( sizeof( T ) >= 4 ) return (bool) top;
      else                              return !~top;
    }
  }

  template<real_scalar_value T, typename N, arm_abi ABI, relative_conditional_expr C>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(neon128_), C const &cond, logical<wide<T, N, ABI>> const &v0) noexcept
  {
    return all_arm_impl(v0, cond);
  }

  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(neon128_), logical<wide<T, N, ABI>> const &v0) noexcept
  {
    return all[ignore_none](v0);
  }
}
