//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/conditional.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/convert.hpp>
#include <eve/detail/top_bits.hpp>

namespace eve::detail
{

  template<real_scalar_value T, typename N, relative_conditional_expr C>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(neon128_), C const &cond, logical<wide<T, N, arm_64_>> const &v0) noexcept
  {
    using u64_1 = typename wide<T, N, arm_64_>::template rebind<std::uint64_t, eve::fixed<1>>;

         if constexpr ( C::is_complete && !C::is_inverted ) return true;
    else if constexpr ( !C::is_complete )  return all_(EVE_RETARGET(cpu_), cond, v0);
    else if constexpr ( eve::current_api >= eve::asimd )
    {
      // I thought about using min here, unlike any (since we do otherwise 2 tests)
      // But
      //   a) I don't have the measurements
      //   b) I suspect when this pops up, compiler might just load u64 directly.
      auto qword = eve::bit_cast(v0, eve::as_<u64_1>{});
      return !~vget_lane_u64(qword, 0);
    }
    else
    {
      if constexpr( sizeof(T) * N() <= 4u ) return all_(EVE_RETARGET(cpu_), cond, v0);

      using u32_2 = typename wide<T, N, arm_64_>::template rebind<std::uint32_t, eve::fixed<2>>;

      auto dwords = eve::bit_cast(v0.bits(), eve::as_<u32_2> {});
      dwords = vpmin_u32(dwords, dwords);

      std::uint32_t combined = vget_lane_u32(dwords, 0);

      if constexpr ( sizeof(T) >= 4 ) return (bool)combined;
      else                            return !~combined;
    }
  }

  template<real_scalar_value T, typename N, relative_conditional_expr C>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(neon128_), C const &cond, logical<wide<T, N, arm_128_>> const &v0) noexcept
  {
    using u32_4 = typename wide<T, N, arm_128_>::template rebind<std::uint32_t, eve::fixed<4>>;

         if constexpr ( C::is_complete && !C::is_inverted ) return true;
    // we still have to convert down here
    else if constexpr ( eve::current_api < eve::asimd && sizeof( T ) >= 2 )
    {
      using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
      auto halved = eve::convert(v0, eve::as_<eve::logical<half_e_t>>{});
      return eve::all[cond](halved);
    }
    else if constexpr ( !C::is_complete ) return all_(EVE_RETARGET(cpu_), cond, v0);
    else if constexpr ( eve::current_api >= eve::asimd )
    {
           if constexpr ( sizeof(T) == 1 )  return vminvq_u8(v0.bits());
      else if constexpr ( sizeof(T) == 2 )  return vminvq_u16(v0.bits());
      else
      {
        // There is no vminvq_u64, so we use vminvq_u32 for everything bigger.
        auto dwords = eve::bit_cast(v0, eve::as_<u32_4>{});
        return vminvq_u32(dwords);
      }
    }
    else  // chars, no asimd
    {
      using u32_4 = typename wide<T, N, arm_128_>::template rebind<std::uint32_t, eve::fixed<4>>;
      auto dwords = eve::bit_cast(v0, eve::as<u32_4>());

      // not the same logic as for uint_32 plain so duplicated.
      return eve::all[ignore_none](dwords == static_cast<std::uint32_t>(-1));
    }
  }
}
