//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/category.hpp>
#include <eve/module/core/regular/combine.hpp>
#include <eve/module/core/constant/zero.hpp>

namespace eve::detail
{
  //================================================================================================
  // convert: float64 -> U
  //================================================================================================
  template<typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N>  convert_impl( EVE_SUPPORTS(neon128_)
                                          , wide<double, N> const& v, as<U> const &tgt
                                          ) noexcept
      requires arm_abi<abi_t<double, N>>
  {
    if constexpr( current_api >= asimd )
    {
      constexpr auto c_i = categorize<wide<double, N>>();
      constexpr auto c_o = categorize<wide<U, N>>();

      // Conversion to float is emulated
      if constexpr( c_i == category::float64x1  )
      {
              if constexpr( c_o == category::int64x1  ) return vcvt_s64_f64(v);
        else  if constexpr( c_o == category::uint64x1 ) return vcvt_u64_f64(v);
        else  return map(convert,v,tgt);
      }
      else if constexpr( c_i == category::float64x2  )
      {
              if constexpr( c_o == category::float32x2) return vcvt_f32_f64(v);
        else  if constexpr( c_o == category::int64x2  ) return vcvtq_s64_f64(v);
        else  if constexpr( c_o == category::uint64x2 ) return vcvtq_u64_f64(v);
        else  if constexpr( c_o == category::int32x2  ) return vmovn_s64(vcvtq_s64_f64(v));
        else  if constexpr( c_o == category::uint32x2 ) return vmovn_u64(vcvtq_u64_f64(v));
        else  return convert( convert(v,as<std::int32_t>()), tgt);
      }
    }
    else
    {
      return map(convert,v,tgt);
    }
  }

  //================================================================================================
  // convert: float32 -> U
  //================================================================================================
  template<typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N>  convert_impl( EVE_SUPPORTS(neon128_)
                                          , wide<float, N> const& v, as<U> const &tgt
                                          ) noexcept
      requires arm_abi<abi_t<float, N>>
  {
    constexpr auto c_o = categorize<wide<U, N>>();

    // (un)signed integers is handled by signed<->unsigned auto-conversion
    // Conversion to double is emulated
          if constexpr( std::same_as<double,U> ) return map(convert,v,tgt);
    else  if constexpr( N::value <= 2 )
    {
      constexpr auto tgt_i32 = as<std::int32_t>{};
      constexpr auto tgt_u32 = as<std::uint32_t>{};

            if constexpr( c_o == category::int32x2   )  return vcvt_s32_f32(v);
      else  if constexpr( c_o == category::int64x2   )  return vmovl_s32(vcvt_s32_f32(v));
      else  if constexpr( c_o && category::signed_   )  return convert(convert(v,tgt_i32), tgt);
      else  if constexpr( c_o == category::uint32x2  )  return vcvt_u32_f32(v);
      else  if constexpr( c_o == category::uint64x2  )  return vmovl_u32(vcvt_u32_f32(v));
      else  if constexpr( c_o && category::unsigned_ )  return convert(convert(v,tgt_u32), tgt);
    }
    else if constexpr( N::value == 4 )
    {
      constexpr auto tgt_i16 = as<std::int16_t>{};
      constexpr auto tgt_u16 = as<std::uint16_t>{};

            if constexpr( c_o == category::int32x4  )  return vcvtq_s32_f32(v);
      else  if constexpr( c_o == category::int16x4  )  return vmovn_s32(vcvtq_s32_f32(v));
      else  if constexpr( c_o == category::int8x8   )  return convert(convert(v,tgt_i16), tgt);
      else  if constexpr( c_o == category::uint32x4 )  return vcvtq_u32_f32(v);
      else  if constexpr( c_o == category::uint16x4 )  return vmovn_u32(vcvtq_u32_f32(v));
      else  if constexpr( c_o == category::uint8x8  )  return convert(convert(v,tgt_u16), tgt);
      // (u)int64x4 is sliced then recombined
      else  if constexpr( sizeof(U) == 8 )
      {
        auto[l,h] = v.slice();
        return wide<U,N>(convert(l,tgt),convert(h,tgt));
      }
    }
  }

  //================================================================================================
  // convert: (u)int64 -> U
  //================================================================================================
  template<integral_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N>  convert_impl( EVE_SUPPORTS(neon128_)
                                          , wide<T, N> const& v, as<U> const &tgt
                                          ) noexcept
      requires arm_abi<abi_t<T, N>> && (sizeof(T) == 8)
  {
    constexpr auto c_i = categorize<wide<T, N>>();
    constexpr auto c_o = categorize<wide<U, N>>();

    // (un)signed integers is handled by signed<->unsigned auto-conversion
    if constexpr( c_i == category::int64x2  )
    {
            if constexpr( c_o == category::int32x2   )  return vmovn_s64(v);
      else  if constexpr( c_o == category::float32x2 )  return vcvt_f32_s32(vmovn_s64(v));
      else  if constexpr( c_o == category::float64x2 )
      {
        if constexpr(current_api >= asimd)  return vcvtq_f64_s64(v); else return map(convert,v,tgt);
      }
      else                                  return convert_integers_chain(v,tgt);
    }
    else  if constexpr( c_i == category::uint64x2 )
    {
            if constexpr( c_o == category::uint32x2  )  return vmovn_u64(v);
      else  if constexpr( c_o == category::float32x2 )  return vcvt_f32_u32(vmovn_u64(v));
      else  if constexpr( c_o == category::float64x2 )
      {
        if constexpr(current_api >= asimd)  return vcvtq_f64_u64(v); else return map(convert,v,tgt);
      }
      else                                  return convert_integers_chain(v,tgt);
    }
    else  if constexpr( current_api >= asimd && c_o == category::float64x1)
    {
            if constexpr( c_i == category::int64x1  ) return vcvt_f64_s64(v);
      else  if constexpr( c_i == category::uint64x1 ) return vcvt_f64_u64(v);
    }
    else  return map(convert,v,tgt);
  }

  //================================================================================================
  // convert: (u)int32 -> U
  //================================================================================================
  template<integral_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N>  convert_impl( EVE_SUPPORTS(neon128_)
                                          , wide<T, N> const& v, as<U> const &tgt
                                          ) noexcept
      requires arm_abi<abi_t<T, N>> && (sizeof(T) == 4)
  {
    constexpr auto c_i = categorize<wide<T, N>>();
    constexpr auto c_o = categorize<wide<U, N>>();

    // (un)signed integers is handled by signed<->unsigned auto-conversion
    // Conversion to double is emulated
          if constexpr( std::same_as<double,U> ) return map(convert,v,tgt);
    // Conversion to ?<8>xN is is a chain of conversion
    else  if constexpr( sizeof(U) == 1        ) return convert_integers_chain(v,tgt);
    // Other conversions use intrinsics
    else  if constexpr( c_i == category::int32x2  )
    {
            if constexpr( c_o == category::float32x2  ) return vcvt_f32_s32(v);
      else  if constexpr( c_o == category::int64x2    ) return vmovl_s32(v);
      else  if constexpr( c_o == category::int64x1    ) return map(convert,v,tgt);
      else  if constexpr( c_o == category::int16x4    )
      {
        if constexpr(N::value == 2)
        {
          // build [v 0] to convert a i32x4 into i16x4 then take the i32x2 lower slice
          // We put 0 in to prevent garbage value to be inserted in the hidden
          return wide<U,fixed<4>>(vmovn_s32(eve::combine(v,zero(as(v))))).slice(lower_);
        }
        else
        {
          return convert( eve::combine(v,zero(as(v))), tgt ).slice(lower_);
        }
      }
    }
    else  if constexpr( c_i == category::uint32x2 )
    {
            if constexpr( c_o == category::float32x2  ) return vcvt_f32_u32(v);
      else  if constexpr( c_o == category::uint64x2   ) return vmovl_u32(v);
      else  if constexpr( c_o == category::uint64x1   ) return map(convert,v,tgt);
      else  if constexpr( c_o == category::uint16x4   )
      {
        if constexpr(N::value == 2)
        {
          // build [v 0] to convert a i32x4 into i16x4 then take the i32x2 lower slice
          // We put 0 in to prevent garbage value to be inserted in the hidden
          return wide<U,fixed<4>>(vmovn_u32(eve::combine(v,zero(as(v))))).slice(lower_);
        }
        else
        {
          return convert( eve::combine(v,zero(as(v))), tgt ).slice(lower_);
        }
      }
    }
    else  if constexpr( c_i == category::int32x4  )
    {
            if constexpr( c_o == category::float32x4  ) return vcvtq_f32_s32(v);
      else  if constexpr( c_o == category::int16x4    ) return vmovn_s32(v);
      else  if constexpr( std::integral<U> && sizeof(U) == 8   )
      {
        using type64 = typename wide<T,N>::template rebind<std::int64_t>;
        auto [l,h] = v.slice(); // 2x i32x2
        return wide<U,N>(type64(vmovl_s32(l)),type64(vmovl_s32(h)));
      }
    }
    else  if constexpr( c_i == category::uint32x4 )
    {
            if constexpr( c_o == category::float32x4 )  return vcvtq_f32_u32(v);
      else  if constexpr( c_o == category::uint16x4   )  return vmovn_u32(v);
      else  if constexpr( std::integral<U> && sizeof(U) == 8   )
      {
        using type64 = wide<upgrade_t<T>,typename N::split_type>;
        auto [l,h] = v.slice(); // 2x u32x2
        return wide<U,N>(type64(vmovl_u32(l)),type64(vmovl_u32(h)));
      }
    }
  }

  //================================================================================================
  // convert: (u)int16 -> U
  template<integral_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N>  convert_impl( EVE_SUPPORTS(neon128_)
                                          , wide<T, N> const& v, as<U> const &tgt
                                          ) noexcept
      requires arm_abi<abi_t<T, N>> && (sizeof(T) == 2)
  {
    constexpr auto c_o = categorize<wide<U, N>>();
    constexpr auto c_i = categorize<wide<T, N>>();

    // (un)signed integers is handled by signed<->unsigned auto-conversion
    // Conversion to double is emulated
    if constexpr( std::same_as<double,U> ) return map(convert,v,tgt);
    // Conversion to ?<64>xN is is a chain of conversion
    else  if constexpr( sizeof(U) == 8  ) return convert_integers_chain(v,tgt);
    // Conversion to ?<32>x4 is manual slicing
    else  if constexpr( N::value == 8 && sizeof(U) == 4 )
    {
      auto [l,h] = v.slice();
      return wide<U,N>(convert(l,tgt),convert(h,tgt));
    }
    // Conversion to smaller than 4 use conversion to 4 + slice
    else  if constexpr(N::value < 4)
    {
      return wide<U,N>(convert( wide<T,fixed<4>>{v.storage()}, tgt).slice(lower_).storage());
    }
    // Other conversions use intrinsics
    else  if constexpr( c_i == category::int16x4 )
    {
            if constexpr( c_o == category::float32x4  ) return vcvtq_f32_s32(vmovl_s16(v));
      else  if constexpr( c_o == category::int32x4    ) return vmovl_s16(v);
      else  if constexpr( c_o == category::int8x8     )
      {
        // Force size to 4 so combine builds a properly sized wide
        wide<T,fixed<4>> base = v.storage();
        return wide<std::int8_t,N>{vmovn_s16(eve::combine(base,zero(as(base))))};
      }
    }
    else  if constexpr( c_i == category::uint16x4 )
    {
            if constexpr( c_o == category::float32x4  ) return vcvtq_f32_u32(vmovl_u16(v));
      else  if constexpr( c_o == category::uint32x4   ) return vmovl_u16(v);
      else  if constexpr( c_o == category::uint8x8    )
      {
        // Force size to 4 so combine builds a properly sized wide
        wide<T,fixed<4>> base = v.storage();
        return wide<downgrade_t<T>,N>(vmovn_u16(eve::combine(base,zero(as(base)))));
      }
    }
    // Remaining cases
    else  if constexpr( c_i == category::int16x8  && c_o == category::int8x8  ) return vmovn_s16(v);
    else  if constexpr( c_i == category::uint16x8 && c_o == category::uint8x8 ) return vmovn_u16(v);
  }

  //================================================================================================
  // convert: (u)int8 -> U
  //================================================================================================
  template<integral_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N>  convert_impl( EVE_SUPPORTS(neon128_)
                                          , wide<T, N> const& v, as<U> const &tgt
                                          ) noexcept
      requires arm_abi<abi_t<T, N>> && (sizeof(T) == 1)
  {
    constexpr auto c_o = categorize<wide<U, N>>();
    constexpr auto c_i = categorize<wide<T, N>>();

    // (un)signed integers is handled by signed<->unsigned auto-conversion
    // Conversion to double and ultra-small wide is emulated
          if constexpr( std::same_as<double,U> || N::value == 1) return map(convert,v,tgt);
    // Conversion to non-int16 is manual slicing
    else  if constexpr( sizeof(U) != 2) return convert(convert(v, as<upgrade_t<T>>{}),tgt);
    // Small conversions use intrinsics
    else  if constexpr( c_i == category::int8x8 )
    {
            if constexpr( c_o == category::int16x8 ) return vmovl_s8(v);
      else  if constexpr( c_o == category::int16x4 ) return vget_low_s16(vmovl_s8(v));
    }
    else  if constexpr( c_i == category::uint8x8 )
    {
            if constexpr( c_o == category::uint16x8 ) return vmovl_u8(v);
      else  if constexpr( c_o == category::uint16x4 ) return vget_low_u16(vmovl_u8(v));
    }
    // Large conversions requires slicing
    else
    {
      auto[l,h] = v.slice();
      return wide<U,N>(convert(l,tgt),convert(h,tgt));
    }
  }
}
