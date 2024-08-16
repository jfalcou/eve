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
//================================================================================================
// Enumerated make
//================================================================================================
template<arithmetic_scalar_value T, typename N, typename... Vs>
EVE_FORCEINLINE auto
make(eve::as<wide<T, N>>, Vs... vs) noexcept
requires rvv_abi<abi_t<T, N>>
{
  static_assert(sizeof...(Vs) == N::value, "[eve::make] - Invalid number of arguments");

  std::array on_stack {static_cast<T>(vs)...};
  return load(ignore_none, safe, as<wide<T, N>> {}, on_stack.data());
}

//================================================================================================
// splat make
//================================================================================================

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                make(eve::as<wide<T, N>>, T x) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto c    = categorize<wide<T, N>>();
  constexpr auto lmul = riscv_rvv_dyn_::getLMUL<T>(N::value);
  if constexpr( match(c, category::float64) )
  {
    if constexpr( lmul == 1 ) return __riscv_vfmv_v_f_f64m1(x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vfmv_v_f_f64m2(x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vfmv_v_f_f64m4(x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vfmv_v_f_f64m8(x, N::value);
  }
  else if constexpr( match(c, category::float32) )
  {
    if constexpr( lmul == -2 ) return __riscv_vfmv_v_f_f32mf2(x, N::value);
    else if constexpr( lmul == 1 ) return __riscv_vfmv_v_f_f32m1(x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vfmv_v_f_f32m2(x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vfmv_v_f_f32m4(x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vfmv_v_f_f32m8(x, N::value);
  }
  else if constexpr( match(c, category::int64) )
  {
    if constexpr( lmul == 1 ) return __riscv_vmv_v_x_i64m1(x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_i64m2(x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_i64m4(x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_i64m8(x, N::value);
  }
  else if constexpr( match(c, category::uint64) )
  {
    if constexpr( lmul == 1 ) return __riscv_vmv_v_x_u64m1(x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_u64m2(x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_u64m4(x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_u64m8(x, N::value);
  }
  else if constexpr( match(c, category::int32) )
  {
    if constexpr( lmul == -2 ) return __riscv_vmv_v_x_i32mf2(x, N::value);
    else if constexpr( lmul == 1 ) return __riscv_vmv_v_x_i32m1(x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_i32m2(x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_i32m4(x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_i32m8(x, N::value);
  }
  else if constexpr( match(c, category::uint32) )
  {
    if constexpr( lmul == -2 ) return __riscv_vmv_v_x_u32mf2(x, N::value);
    else if constexpr( lmul == 1 ) return __riscv_vmv_v_x_u32m1(x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_u32m2(x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_u32m4(x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_u32m8(x, N::value);
  }
  else if constexpr( match(c, category::int16) )
  {
    if constexpr( lmul == -4 ) return __riscv_vmv_v_x_i16mf4(x, N::value);
    else if constexpr( lmul == -2 ) return __riscv_vmv_v_x_i16mf2(x, N::value);
    else if constexpr( lmul == 1 ) return __riscv_vmv_v_x_i16m1(x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_i16m2(x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_i16m4(x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_i16m8(x, N::value);
  }
  else if constexpr( match(c, category::uint16) )
  {
    if constexpr( lmul == -4 ) return __riscv_vmv_v_x_u16mf4(x, N::value);
    else if constexpr( lmul == -2 ) return __riscv_vmv_v_x_u16mf2(x, N::value);
    else if constexpr( lmul == 1 ) return __riscv_vmv_v_x_u16m1(x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_u16m2(x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_u16m4(x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_u16m8(x, N::value);
  }
  else if constexpr( match(c, category::int8) )
  {
    if constexpr( lmul == -8 ) return __riscv_vmv_v_x_i8mf8(x, N::value);
    else if constexpr( lmul == -4 ) return __riscv_vmv_v_x_i8mf4(x, N::value);
    else if constexpr( lmul == -2 ) return __riscv_vmv_v_x_i8mf2(x, N::value);
    else if constexpr( lmul == 1 ) return __riscv_vmv_v_x_i8m1(x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_i8m2(x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_i8m4(x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_i8m8(x, N::value);
  }
  else if constexpr( match(c, category::uint8) )
  {
    if constexpr( lmul == -8 ) return __riscv_vmv_v_x_u8mf8(x, N::value);
    else if constexpr( lmul == -4 ) return __riscv_vmv_v_x_u8mf4(x, N::value);
    else if constexpr( lmul == -2 ) return __riscv_vmv_v_x_u8mf2(x, N::value);
    else if constexpr( lmul == 1 ) return __riscv_vmv_v_x_u8m1(x, N::value);
    else if constexpr( lmul == 2 ) return __riscv_vmv_v_x_u8m2(x, N::value);
    else if constexpr( lmul == 4 ) return __riscv_vmv_v_x_u8m4(x, N::value);
    else if constexpr( lmul == 8 ) return __riscv_vmv_v_x_u8m8(x, N::value);
  }
}

//================================================================================================
// logical cases
//================================================================================================
template<arithmetic_scalar_value T, typename N, typename... Vs>
EVE_FORCEINLINE logical<wide<T, N>>
                make(as<logical<wide<T, N>>>, Vs... vs) noexcept
requires rvv_abi<abi_t<T, N>>
{
  using bits_type = typename logical<wide<T, N>>::bits_type;
  using e_t       = element_type_t<bits_type>;

  auto bits = make(as<bits_type> {}, (vs ? static_cast<e_t>(-1) : static_cast<e_t>(0))...);
  return bit_cast(self_greater(bits, static_cast<e_t>(0)), as<logical<wide<T, N>>> {});
}

}
