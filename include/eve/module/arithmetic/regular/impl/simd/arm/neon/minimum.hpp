//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/detail/function/reduce.hpp>
#include <eve/module/arithmetic/min.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE T minimum_( EVE_SUPPORTS(neon128_)
                            , wide<T,N> v
                            ) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T,N>>();

    if constexpr ( eve::current_api >= eve::asimd )
    {
            if constexpr( N::value == 1           ) return v.get(0);
      else  if constexpr( c == category::float64x2) return vminvq_f64(v);
      else  if constexpr( c == category::float32x2) return vminv_f32 (v);
      else  if constexpr( c == category::float32x4) return vminvq_f32(v);
      else  if constexpr( c == category::int32x2  ) return vminv_s32 (v);
      else  if constexpr( c == category::int32x4  ) return vminvq_s32(v);
      else  if constexpr( c == category::uint32x2 ) return vminv_u32 (v);
      else  if constexpr( c == category::uint32x4 ) return vminvq_u32(v);
      else  if constexpr( c == category::int16x4  ) return vminv_s16 (v);
      else  if constexpr( c == category::int16x8  ) return vminvq_s16(v);
      else  if constexpr( c == category::uint16x4 ) return vminv_u16 (v);
      else  if constexpr( c == category::uint16x8 ) return vminvq_u16(v);
      else  if constexpr( c == category::int8x8   ) return vminv_s8  (v);
      else  if constexpr( c == category::int8x16  ) return vminvq_s8 (v);
      else  if constexpr( c == category::uint8x8  ) return vminv_u8  (v);
      else  if constexpr( c == category::uint8x16 ) return vminvq_u8 (v);
      else  return butterfly_reduction(v, eve::min).get(0);
    }
    else
    {
      return splat(minimum)(v).get(0);
    }
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T,N> minimum_( EVE_SUPPORTS(neon128_)
                                        , splat_type const&, wide<T,N> const& v
                                        ) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    if constexpr ( eve::current_api >= eve::asimd )
    {
      return wide<T,N>( minimum(v) );
    }
    else
    {
      constexpr auto pairwise_min = []<typename W>(W const& a, W const& b)
      {
        constexpr auto c = categorize<W>();

              if constexpr( c == category::float32x2) return vpmin_f32(a,b);
        else  if constexpr( c == category::int32x2  ) return vpmin_s32(a,b);
        else  if constexpr( c == category::uint32x2 ) return vpmin_u32(a,b);
        else  if constexpr( c == category::int16x4  ) return vpmin_s16(a,b);
        else  if constexpr( c == category::uint16x4 ) return vpmin_u16(a,b);
        else  if constexpr( c == category::int8x8   ) return vpmin_s8(a,b);
        else  if constexpr( c == category::uint8x8  ) return vpmin_u8(a,b);
      };

      using type = wide<T,N>;

            if constexpr( N::value == 1 ) return v;
      else  if constexpr( N::value == 2 ) return type(eve::min(v.get(0),v.get(1)));
      else  if constexpr( std::same_as<abi_t<T, N>,arm_64_> )
      {
        if(N::value == expected_cardinal_v<T,abi_t<T, N>>)
        {
          wide<T,N> s = pairwise_min(v,v);
          if constexpr(N::value >= 2  ) s = pairwise_min(s,s);
          if constexpr(N::value >= 4  ) s = pairwise_min(s,s);
          if constexpr(N::value >= 8  ) s = pairwise_min(s,s);
          return s;
        }
        else
        {
          return butterfly_reduction(v, eve::min);
        }
      }
      else  if constexpr( std::same_as<abi_t<T, N>,arm_128_> )
      {
        auto [l,h] = v.slice();
        if constexpr(N::value >= 4  ) l = pairwise_min(l,h);
        if constexpr(N::value >= 8  ) l = pairwise_min(l,l);
        if constexpr(N::value >= 16 ) l = pairwise_min(l,l);
        l = pairwise_min(l,l);

        return wide<T,N>(l,l);
      }
    }
  }
}
