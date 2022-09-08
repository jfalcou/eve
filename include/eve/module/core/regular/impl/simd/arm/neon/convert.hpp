//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/combine.hpp>

namespace eve::detail
{
//================================================================================================
// convert: float64 -> U
//================================================================================================
template<typename N, real_scalar_value U>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(neon128_),
                             wide<double, N> const                &v,
                             as<U> const                          &tgt) noexcept requires arm_abi<abi_t<double, N>>
{
  using enum category;

  constexpr auto c_i = categorize<wide<double, N>>();
  constexpr auto c_o = categorize<wide<U, N>>();

  if constexpr( c_i == float64x1 && c_o == int64x1 ) return vcvt_s64_f64(v);
  else if constexpr( c_i == float64x1 && c_o == uint64x1 ) return vcvt_u64_f64(v);
  else if constexpr( c_i == float64x1 ) return map(convert, v, tgt);
  else if constexpr( c_i == float64x2 && c_o == float32x2 ) return vcvt_f32_f64(v);
  else if constexpr( c_i == float64x2 && c_o == int64x2 ) return vcvtq_s64_f64(v);
  else if constexpr( c_i == float64x2 && c_o == uint64x2 ) return vcvtq_u64_f64(v);
  else if constexpr( c_i == float64x2 && c_o == int32x2 ) return vmovn_s64(vcvtq_s64_f64(v));
  else if constexpr( c_i == float64x2 && c_o == uint32x2 ) return vmovn_u64(vcvtq_u64_f64(v));
  else if constexpr( c_i == float64x2 ) return convert(convert(v, as<std::int32_t>()), tgt);
}

//================================================================================================
// convert: float32 -> U
//================================================================================================
template<typename N, real_scalar_value U>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(neon128_),
                             wide<float, N> const                &v,
                             as<U> const                         &tgt) noexcept requires arm_abi<abi_t<float, N>>
{
  using enum category;
  constexpr auto c_o   = categorize<wide<U, N>>();
  constexpr auto api64 = current_api >= asimd;
  constexpr auto t_i32 = as<std::int32_t> {};
  constexpr auto t_u32 = as<std::uint32_t> {};

  if constexpr( N {} <= 2 )
  {
    if constexpr( c_o == float64x2 && api64 ) return vcvt_f64_f32(v);
    else if constexpr( c_o == int64x2 && api64 ) return convert(convert(v, as<double> {}), tgt);
    else if constexpr( c_o == uint64x2 && api64 ) return convert(convert(v, as<double> {}), tgt);
    else if constexpr( c_o == int32x2 ) return vcvt_s32_f32(v);
    else if constexpr( c_o == uint32x2 ) return vcvt_u32_f32(v);
    else if constexpr( sizeof(U) == 8 ) return map(convert, v, tgt);
    else if constexpr( match(c_o, signed_   ) ) return convert(convert(v, t_i32), tgt);
    else if constexpr( match(c_o, unsigned_ ) ) return convert(convert(v, t_u32), tgt);
  }
  else if constexpr( N {} == 4 )
  {
    constexpr auto t_i16 = as<std::int16_t> {};
    constexpr auto t_u16 = as<std::uint16_t> {};

    if constexpr( c_o == int32x4 ) return vcvtq_s32_f32(v);
    else if constexpr( c_o == uint32x4 ) return vcvtq_u32_f32(v);
    else if constexpr( c_o == int16x4 ) return convert(convert(v, t_i32), tgt);
    else if constexpr( c_o == uint16x4 ) return convert(convert(v, t_u32), tgt);
    else if constexpr( c_o == int8x8 ) return convert(convert(v, t_i16), tgt);
    else if constexpr( c_o == uint8x8 ) return convert(convert(v, t_u16), tgt);
    else if constexpr( sizeof(U) == 8 ) return convert_slice(v, tgt);
  }
}

//================================================================================================
// convert: (u)int64 -> U
//================================================================================================
template<integral_scalar_value T, typename N, real_scalar_value U>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(neon128_),
                             wide<T, N> const                &v,
                             as<U> const                     &tgt) noexcept requires arm_abi<abi_t<T, N>> &&(sizeof(T) == 8)
{
  using enum category;

  constexpr auto c_i     = categorize<wide<T, N>>();
  constexpr auto c_o     = categorize<wide<U, N>>();
  constexpr auto api_a64 = current_api >= asimd;
  using i32_t            = as<std::int32_t>;
  using u32_t            = as<std::uint32_t>;

  if constexpr( c_i == int64x2 && c_o == int32x2 ) return vmovn_s64(v);
  else if constexpr( c_i == uint64x2 && c_o == uint32x2 ) return vmovn_u64(v);
  else if constexpr( c_i == int64x2 && c_o == float32x2 ) return convert(convert(v, i32_t {}), tgt);
  else if constexpr( c_i == uint64x2 && c_o == float32x2 )
    return convert(convert(v, u32_t {}), tgt);
  else if constexpr( c_i == int64x2 && c_o == float64x2 && api_a64 ) return vcvtq_f64_s64(v);
  else if constexpr( c_i == uint64x2 && c_o == float64x2 && api_a64 ) return vcvtq_f64_u64(v);
  else if constexpr( c_i == int64x1 && c_o == float64x1 && api_a64 ) return vcvt_f64_s64(v);
  else if constexpr( c_i == uint64x1 && c_o == float64x1 && api_a64 ) return vcvt_f64_u64(v);
  else if constexpr( std::is_floating_point_v<U> ) return map(convert, v, tgt);
  else return convert_integers_chain(v, tgt);
}

//================================================================================================
// convert: (u)int32 -> U
//================================================================================================
template<integral_scalar_value T, typename N, real_scalar_value U>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(neon128_),
                             wide<T, N> const                &v,
                             as<U> const                     &tgt) noexcept requires arm_abi<abi_t<T, N>> &&(sizeof(T) == 4)
{
  using enum category;
  constexpr auto c_i = categorize<wide<T, N>>();
  constexpr auto c_o = categorize<wide<U, N>>();

  if constexpr( c_i == int32x2 && c_o == int64x2 ) return vmovl_s32(v);
  else if constexpr( c_i == uint32x2 && c_o == uint64x2 ) return vmovl_u32(v);
  else if constexpr( c_i == int32x2 && c_o == int64x1 ) return map(convert, v, tgt);
  else if constexpr( c_i == uint32x2 && c_o == uint64x1 ) return map(convert, v, tgt);
  else if constexpr( c_i == int32x4 && c_o == float32x4 ) return vcvtq_f32_s32(v);
  else if constexpr( c_i == int32x2 && c_o == float32x2 ) return vcvt_f32_s32(v);
  else if constexpr( c_i == uint32x4 && c_o == float32x4 ) return vcvtq_f32_u32(v);
  else if constexpr( c_i == uint32x2 && c_o == float32x2 ) return vcvt_f32_u32(v);
  else if constexpr( c_i == int32x4 && c_o == int16x4 ) return vmovn_s32(v);
  else if constexpr( c_i == uint32x4 && c_o == uint16x4 ) return vmovn_u32(v);
  else if constexpr( sizeof(U) == 2 ) return convert_integers_shuffle(v, tgt);
  else if constexpr( sizeof(U) == 1 ) return convert_integers_chain(v, tgt);
  else if constexpr( std::same_as<double, U> ) return convert(convert(v, as<upgrade_t<T>> {}), tgt);
  else return convert_impl(EVE_RETARGET(cpu_), v, tgt);
}

//================================================================================================
// convert: (u)int16 -> U
template<integral_scalar_value T, typename N, real_scalar_value U>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(neon128_),
                             wide<T, N> const                &v,
                             as<U> const                     &tgt) noexcept requires arm_abi<abi_t<T, N>> &&(sizeof(T) == 2)
{
  using enum category;
  constexpr auto c_o = categorize<wide<U, N>>();
  constexpr auto c_i = categorize<wide<T, N>>();
  using i32_t        = as<std::int32_t>;
  using f32_t        = as<float>;
  using u32_t        = as<std::uint32_t>;

  if constexpr( std::same_as<double, U> ) return convert(convert(v, f32_t {}), tgt);
  else if constexpr( sizeof(U) == 8 ) return convert_integers_chain(v, tgt);
  else if constexpr( N {} == 8 && sizeof(U) == 4 ) return convert_slice(v, tgt);
  else if constexpr( c_i == int16x4 && c_o == float32x4 ) return convert(convert(v, i32_t {}), tgt);
  else if constexpr( c_i == uint16x4 && c_o == float32x4 )
    return convert(convert(v, u32_t {}), tgt);
  else if constexpr( c_i == int16x8 && c_o == int8x8 ) return vmovn_s16(v);
  else if constexpr( c_i == int16x4 && c_o == int32x4 ) return vmovl_s16(v);
  else if constexpr( c_i == uint16x8 && c_o == uint8x8 ) return vmovn_u16(v);
  else if constexpr( c_i == uint16x4 && c_o == uint32x4 ) return vmovl_u16(v);
  else if constexpr( N {} < 4 )
  {
    return wide<U, N>(convert(wide<T, fixed<4>> {v.storage()}, tgt).slice(lower_).storage());
  }
  else
  {
    // Zero is optimized out by the compiler
    wide<T, fixed<4>> base = v.storage(), z {0};
    return wide<U, N> {convert(eve::combine(base, z), tgt).storage()};
  }
}

//================================================================================================
// convert: (u)int8 -> U
//================================================================================================
template<integral_scalar_value T, typename N, real_scalar_value U>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(neon128_),
                             wide<T, N> const                &v,
                             as<U> const                     &tgt) noexcept requires arm_abi<abi_t<T, N>> &&(sizeof(T) == 1)
{
  using enum category;
  constexpr auto c_o = categorize<wide<U, N>>();
  constexpr auto c_i = categorize<wide<T, N>>();

  if constexpr( c_i == int8x8 && c_o == int16x8 ) return vmovl_s8(v);
  else if constexpr( c_i == uint8x8 && c_o == uint16x8 ) return vmovl_u8(v);
  else if constexpr( c_i == int8x8 && c_o == int16x4 ) return vget_low_s16(vmovl_s8(v));
  else if constexpr( c_i == uint8x8 && c_o == uint16x4 ) return vget_low_u16(vmovl_u8(v));
  else if constexpr( std::same_as<double, U> && current_api < asimd ) return map(convert, v, tgt);
  else if constexpr( sizeof(U) != 2 ) return convert(convert(v, as<upgrade_t<T>> {}), tgt);
  else return convert_slice(v, tgt);
}
}
