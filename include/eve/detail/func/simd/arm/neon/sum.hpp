//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/module/core/regular/slide_right.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T,N> arm_cleanup(wide<T,N> v) noexcept
  {
    // Clean up potential garbage
    using ec_t = expected_cardinal_t<T,arm_64_>;
    if constexpr(N::value < ec_t::value)
    {
      v = bit_cast( slide_right ( bit_cast(v,as<wide<T,ec_t>>())
                                , index<ec_t::value - N::value>
                                )
                  , as(v)
                  );
    }

    return v;
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T,N> arm_sum_impl(wide<T,N> v) noexcept
  {
    constexpr auto c = categorize<wide<T, N>>();

          if constexpr( c== category::float32x2 ) return vpadd_f32(v,v);
    else  if constexpr( c== category::uint32x2  ) return vpadd_u32(v,v);
    else  if constexpr( c== category::int32x2   ) return vpadd_s32(v,v);
    else  if constexpr( c== category::uint16x4  ) return vpadd_u16(v,v);
    else  if constexpr( c== category::int16x4   ) return vpadd_s16(v,v);
    else  if constexpr( c== category::uint8x8   ) return vpadd_u8(v,v);
    else  if constexpr( c== category::int8x8    ) return vpadd_s8(v,v);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T,N> sum_( EVE_SUPPORTS(neon128_), splat_type const&, wide<T,N> v) noexcept
  requires arm_abi<abi_t<T, N>>
  {
          if constexpr(N::value == 1)  return v;
    else  if constexpr(current_api >= asimd)
    {
      return wide<T,N>(sum(v));
    }
    else
    {
      if constexpr( std::same_as<abi_t<T,N>, arm_64_> )
      {
        v = arm_cleanup(v);
        if constexpr(sizeof(T) <= 4)  v = arm_sum_impl(v);
        if constexpr(sizeof(T) <= 2)  v = arm_sum_impl(v);
        if constexpr(sizeof(T) <= 1)  v = arm_sum_impl(v);
        return v;
      }
      else
      {
        if constexpr(sizeof(T) == 8) return wide<T,N>{v.get(0)+v.get(1)};
        else
        {
          auto [l, h] = v.slice();
          l = splat(sum)(l+h);
          return wide<T,N>{l, l};
        }
      }
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE T sum_( EVE_SUPPORTS(neon128_), wide<T,N> v) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    if constexpr(N::value == 1)  return v.get(0);
    else
    {
      if constexpr(current_api >= asimd)
      {
        v = arm_cleanup(v);
        constexpr auto c = categorize<wide<T, N>>();

              if constexpr( c== category::float64x2 ) return vaddvq_f64(v);
        else  if constexpr( c== category::float32x2 ) return vaddv_f32(v);
        else  if constexpr( c== category::float32x4 ) return vaddvq_f32(v);
        else  if constexpr( c== category::uint64x2  ) return vaddvq_u64(v);
        else  if constexpr( c== category::int64x2   ) return vaddvq_s64(v);
        else  if constexpr( c== category::uint32x2  ) return vaddv_u32(v);
        else  if constexpr( c== category::uint32x4  ) return vaddvq_u32(v);
        else  if constexpr( c== category::int32x2   ) return vaddv_s32(v);
        else  if constexpr( c== category::int32x4   ) return vaddvq_s32(v);
        else  if constexpr( c== category::uint16x4  ) return vaddv_u16(v);
        else  if constexpr( c== category::uint16x8  ) return vaddvq_u16(v);
        else  if constexpr( c== category::int16x4   ) return vaddv_s16(v);
        else  if constexpr( c== category::int16x8   ) return vaddvq_s16(v);
        else  if constexpr( c== category::uint8x8   ) return vaddv_u8(v);
        else  if constexpr( c== category::uint8x16  ) return vaddvq_u8(v);
        else  if constexpr( c== category::int8x8    ) return vaddv_s8(v);
        else  if constexpr( c== category::int8x16   ) return vaddvq_s8(v);
      }
      else
      {
              if constexpr( std::same_as<abi_t<T,N>, arm_64_> ) return splat(sum)(v).get(0);
        else  if constexpr(sizeof(T) == 8)                      return v.get(0)+v.get(1);
        else
        {
          auto [l,h] = v.slice();
          return splat(eve::detail::sum)(l+h).get(0);
        }
      }
    }
  }
}
