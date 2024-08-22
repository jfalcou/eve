//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/fundamental_cardinal.hpp>
#include <eve/as.hpp>
#include <eve/concept/options.hpp>
#include <eve/conditional.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/function/load.hpp>
#include <eve/detail/function/simd/riscv/friends.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/regular/safe.hpp>
#include <eve/traits/as_integer.hpp>

namespace eve::detail
{

template<arithmetic_scalar_value T, typename N>
requires rvv_abi<abi_t<T, N>>
EVE_FORCEINLINE wide<T, N>
                rvv_make_splat(eve::as<wide<T, N>>, T x) noexcept
{
  constexpr auto c    = categorize<wide<T, N>>();
  constexpr auto lmul = rvv_lmul_v<T, N>;
  wide<T, N>     fill_zero;
  if constexpr( N::value < eve::fundamental_cardinal_v<T> )
  {
    auto tgt              = as<wide<T, eve::fundamental_cardinal<T>>> {};
    auto fundamental_zero = rvv_make_splat(tgt, static_cast<T>(0));
    fill_zero             = bit_cast(fundamental_zero, eve::as<wide<T, N>> {});
  }

  if constexpr( match(c, category::float64) )
  {
    if constexpr( lmul == 1 ) return __riscv_vfmv_v_f_f64m1_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vfmv_v_f_f64m2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vfmv_v_f_f64m4_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vfmv_v_f_f64m8_tu(fill_zero, x, N::value);
  }
  else if constexpr( match(c, category::float32) )
  {
    if constexpr( lmul == -2 ) return __riscv_vfmv_v_f_f32mf2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 1 ) return __riscv_vfmv_v_f_f32m1_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vfmv_v_f_f32m2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vfmv_v_f_f32m4_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vfmv_v_f_f32m8_tu(fill_zero, x, N::value);
  }
  else if constexpr( match(c, category::int64) )
  {
    if constexpr( lmul == 1 ) return __riscv_vmv_v_x_i64m1_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_i64m2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_i64m4_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_i64m8_tu(fill_zero, x, N::value);
  }
  else if constexpr( match(c, category::uint64) )
  {
    if constexpr( lmul == 1 ) return __riscv_vmv_v_x_u64m1_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_u64m2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_u64m4_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_u64m8_tu(fill_zero, x, N::value);
  }
  else if constexpr( match(c, category::int32) )
  {
    if constexpr( lmul == -2 ) return __riscv_vmv_v_x_i32mf2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 1 ) return __riscv_vmv_v_x_i32m1_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_i32m2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_i32m4_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_i32m8_tu(fill_zero, x, N::value);
  }
  else if constexpr( match(c, category::uint32) )
  {
    if constexpr( lmul == -2 ) return __riscv_vmv_v_x_u32mf2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 1 ) return __riscv_vmv_v_x_u32m1_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_u32m2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_u32m4_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_u32m8_tu(fill_zero, x, N::value);
  }
  else if constexpr( match(c, category::int16) )
  {
    if constexpr( lmul == -4 ) return __riscv_vmv_v_x_i16mf4_tu(fill_zero, x, N::value);
    else if constexpr( lmul == -2 ) return __riscv_vmv_v_x_i16mf2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 1 ) return __riscv_vmv_v_x_i16m1_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_i16m2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_i16m4_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_i16m8_tu(fill_zero, x, N::value);
  }
  else if constexpr( match(c, category::uint16) )
  {
    if constexpr( lmul == -4 ) return __riscv_vmv_v_x_u16mf4_tu(fill_zero, x, N::value);
    else if constexpr( lmul == -2 ) return __riscv_vmv_v_x_u16mf2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 1 ) return __riscv_vmv_v_x_u16m1_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_u16m2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_u16m4_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_u16m8_tu(fill_zero, x, N::value);
  }
  else if constexpr( match(c, category::int8) )
  {
    if constexpr( lmul == -8 ) return __riscv_vmv_v_x_i8mf8_tu(fill_zero, x, N::value);
    else if constexpr( lmul == -4 ) return __riscv_vmv_v_x_i8mf4_tu(fill_zero, x, N::value);
    else if constexpr( lmul == -2 ) return __riscv_vmv_v_x_i8mf2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 1 ) return __riscv_vmv_v_x_i8m1_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_i8m2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_i8m4_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_i8m8_tu(fill_zero, x, N::value);
  }
  else if constexpr( match(c, category::uint8) )
  {
    if constexpr( lmul == -8 ) return __riscv_vmv_v_x_u8mf8_tu(fill_zero, x, N::value);
    else if constexpr( lmul == -4 ) return __riscv_vmv_v_x_u8mf4_tu(fill_zero, x, N::value);
    else if constexpr( lmul == -2 ) return __riscv_vmv_v_x_u8mf2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 1 ) return __riscv_vmv_v_x_u8m1_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_u8m2_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_u8m4_tu(fill_zero, x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_u8m8_tu(fill_zero, x, N::value);
  }
}

template<arithmetic_scalar_value T, typename N, arithmetic_scalar_value... Vs>
requires rvv_abi<abi_t<T, N>>
EVE_FORCEINLINE wide<T, N>
                rvv_make_enumerated(eve::as<wide<T, N>>, Vs... vs)
{
  static_assert(sizeof...(Vs) == N::value, "[eve::make] - Invalid number of arguments");
  std::array on_stack {static_cast<T>(vs)...};
  return load(ignore_none, safe, as<wide<T, N>> {}, on_stack.data());
}

template<callable_options O, arithmetic_scalar_value T, typename N, typename V1, typename... Vs>
requires rvv_abi<abi_t<T, N>>
EVE_FORCEINLINE auto
make_(EVE_REQUIRES(rvv_), O const&, eve::as<wide<T, N>> tgt, V1 v1, Vs... vs) noexcept
{
  if constexpr( sizeof...(Vs) == 0 ) return rvv_make_splat(tgt, v1);
  else return rvv_make_enumerated(tgt, v1, vs...);
}

//================================================================================================
// logical cases
//================================================================================================
template<callable_options O, arithmetic_scalar_value T, typename N, typename V1, typename... Vs>
EVE_FORCEINLINE logical<wide<T, N>>
make_(EVE_REQUIRES(rvv_), O const&, as<logical<wide<T, N>>>, V1 v1, Vs... vs) noexcept
requires rvv_abi<abi_t<T, N>>
{
  using bits_type = typename logical<wide<T, N>>::bits_type;
  using e_t       = element_type_t<bits_type>;
  bits_type bits;
  auto      tgt_wide = as<bits_type> {};
  if constexpr( sizeof...(Vs) == 0 )
    bits = rvv_make_splat(tgt_wide, v1 ? static_cast<e_t>(-1) : static_cast<e_t>(0));
  else
    bits = rvv_make_enumerated(tgt_wide,
                               v1 ? static_cast<e_t>(-1) : static_cast<e_t>(0),
                               (vs ? static_cast<e_t>(-1) : static_cast<e_t>(0))...);
  auto logic_tgt = as<logical<wide<T, N>>> {};
  if constexpr( N::value < eve::fundamental_cardinal_v<T> )
  {
    auto tgt          = as<wide<e_t, fundamental_cardinal<T>>> {};
    auto full_bits    = bit_cast(bits, tgt);
    auto full_logical = full_bits > static_cast<e_t>(0);
    return simd_cast(full_logical, logic_tgt);
  }
  else return simd_cast(bits > static_cast<e_t>(0), logic_tgt);
}

}
