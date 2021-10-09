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

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T,N> arm_sum_impl(wide<T,N> v, wide<T,N> w) noexcept
  {
    constexpr auto c = categorize<wide<T, N>>();

          if constexpr( c== category::float32x2 ) return vpadd_f32(v,w);
    else  if constexpr( c== category::uint32x2  ) return vpadd_u32(v,w);
    else  if constexpr( c== category::int32x2   ) return vpadd_s32(v,w);
    else  if constexpr( c== category::uint16x4  ) return vpadd_u16(v,w);
    else  if constexpr( c== category::int16x4   ) return vpadd_s16(v,w);
    else  if constexpr( c== category::uint8x8   ) return vpadd_u8(v,w);
    else  if constexpr( c== category::int8x8    ) return vpadd_s8(v,w);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T,N> sum_( EVE_SUPPORTS(neon128_), splat_type const&, wide<T,N> v) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    if constexpr( std::same_as<abi_t<T,N>, arm_64_> )
    {
      if constexpr  (N::value == 1)  return v;
      else
      {
        if constexpr(sizeof(T) <= 4)  v = arm_sum_impl(v,v);
        if constexpr(sizeof(T) <= 2)  v = arm_sum_impl(v,v);
        if constexpr(sizeof(T) <= 1)  v = arm_sum_impl(v,v);
        return v;
      }
    }
    else
    {
      if constexpr(sizeof(T) == 8)
      {
        return wide<T,N>{v.get(0)+v.get(1)};
      }
      else
      {
        auto [l, h] = v.slice();
        l = splat(sum)(l+h);
        return wide<T,N>{l, l};
      }
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE T sum_( EVE_SUPPORTS(neon128_), wide<T,N> v) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    if constexpr( std::same_as<abi_t<T,N>, arm_64_> ) return splat(sum)(v).get(0);
    else
    {
      if constexpr(sizeof(T) == 8)
      {
        return v.get(0)+v.get(1);
      }
      else
      {
        auto [l,h] = v.slice();
        wide<T, typename N::split_type> s = arm_sum_impl(l,h);
                                        s = splat(eve::detail::sum)(s);
        return s.get(0);
      }
    }
  }
}
