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

namespace eve::detail
{
  template <typename T, typename N, typename C>
  EVE_FORCEINLINE bool all_arm_impl(logical<wide<T, N, arm_64_>> v0, C const & cond)
  {
    using l_t = logical<wide<T, N, arm_64_>>;
    if constexpr ( C::is_complete && !C::is_inverted ) return true;
    else
    {
      if constexpr ( !C::is_complete ) v0 = v0 || cond.mask_inverted(eve::as_<l_t>{});

      if constexpr( N::value == 1 ) return v0.get(0);
      else
      {
        using u32_2    = wide<std::uint32_t, eve::fixed<2>, arm_64_>;
        auto as_uint32 = eve::bit_cast(v0.bits(), eve::as_<u32_2> {});

        if constexpr( sizeof(T) * N() > 4u ) as_uint32 = vpmin_u32(as_uint32, as_uint32);

        std::uint32_t combined = vget_lane_u32(as_uint32, 0);

              if constexpr ( sizeof(T) >= 4 )       return (bool)combined;
        else  if constexpr ( sizeof(T) * N() == 8 ) return !~combined;
        else
        {
          std::uint32_t expected = [] {
            std::uint64_t res = 1;
            res <<= sizeof(T) * N() * 8;
            res -= 1;
            return res;
          }();

          return (combined & expected) == expected;
        }
      }
    }
  }

  template <typename T, typename N, typename C>
  EVE_FORCEINLINE bool all_arm_impl(logical<wide<T, N, arm_128_>> v0, C const & cond)
  {
    using l_t = logical<wide<T, N, arm_128_>>;

         if constexpr ( C::is_complete && !C::is_inverted ) return true;
    else if constexpr ( sizeof( T ) >= 2 )
    {
      using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
      auto halved = eve::convert(v0, eve::as_<eve::logical<half_e_t>>{});
      return all_arm_impl(halved, cond);
    }
    else
    {
      if constexpr ( !C::is_complete ) v0 = v0 || cond.mask_inverted(eve::as_<l_t>{});
      auto [l, h] = v0.slice();
      return all_arm_impl(l && h, ignore_none);
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
    return all_arm_impl(v0, ignore_none);
  }
}
