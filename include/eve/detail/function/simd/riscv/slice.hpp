//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/category.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/implementation.hpp>

// Return first or second part of vector.

namespace eve::detail
{

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, typename N::split_type>
                riscv_lmul_trunc(wide<T, N> a) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto c        = categorize<wide<T, typename N::split_type>>();
  constexpr auto out_lmul = riscv_rvv_dyn_::getLMUL<T>(N::split_type::value);
  constexpr auto in_lmul  = riscv_rvv_dyn_::getLMUL<T>(N::value);
  if constexpr( out_lmul == in_lmul ) return a.storage();
  else
  {
    static_assert(in_lmul > out_lmul);

    if constexpr( match(c, category::float64) )
    {
      if constexpr( out_lmul == 1 ) return __riscv_vlmul_trunc_f64m1(a);
      else if constexpr( out_lmul == 2 ) return __riscv_vlmul_trunc_f64m2(a);
      else if constexpr( out_lmul == 4 ) return __riscv_vlmul_trunc_f64m4(a);
    }
    else if constexpr( match(c, category::int64) )
    {
      if constexpr( out_lmul == 1 ) return __riscv_vlmul_trunc_i64m1(a);
      else if constexpr( out_lmul == 2 ) return __riscv_vlmul_trunc_i64m2(a);
      else if constexpr( out_lmul == 4 ) return __riscv_vlmul_trunc_i64m4(a);
    }
    else if constexpr( match(c, category::uint64) )
    {
      if constexpr( out_lmul == 1 ) return __riscv_vlmul_trunc_u64m1(a);
      else if constexpr( out_lmul == 2 ) return __riscv_vlmul_trunc_u64m2(a);
      else if constexpr( out_lmul == 4 ) return __riscv_vlmul_trunc_u64m4(a);
    }
    else if constexpr( match(c, category::float32) )
    {
      if constexpr( out_lmul == -2 ) return __riscv_vlmul_trunc_f32mf2(a);
      else if constexpr( out_lmul == 1 ) return __riscv_vlmul_trunc_f32m1(a);
      else if constexpr( out_lmul == 2 ) return __riscv_vlmul_trunc_f32m2(a);
      else if constexpr( out_lmul == 4 ) return __riscv_vlmul_trunc_f32m4(a);
    }
    else if constexpr( match(c, category::int32) )
    {
      if constexpr( out_lmul == -2 ) return __riscv_vlmul_trunc_i32mf2(a);
      else if constexpr( out_lmul == 1 ) return __riscv_vlmul_trunc_i32m1(a);
      else if constexpr( out_lmul == 2 ) return __riscv_vlmul_trunc_i32m2(a);
      else if constexpr( out_lmul == 4 ) return __riscv_vlmul_trunc_i32m4(a);
    }
    else if constexpr( match(c, category::uint32) )
    {
      if constexpr( out_lmul == -2 ) return __riscv_vlmul_trunc_u32mf2(a);
      else if constexpr( out_lmul == 1 ) return __riscv_vlmul_trunc_u32m1(a);
      else if constexpr( out_lmul == 2 ) return __riscv_vlmul_trunc_u32m2(a);
      else if constexpr( out_lmul == 4 ) return __riscv_vlmul_trunc_u32m4(a);
    }
    else if constexpr( match(c, category::int16) )
    {
      if constexpr( out_lmul == -4 ) return __riscv_vlmul_trunc_i16mf4(a);
      else if constexpr( out_lmul == -2 ) return __riscv_vlmul_trunc_i16mf2(a);
      else if constexpr( out_lmul == 1 ) return __riscv_vlmul_trunc_i16m1(a);
      else if constexpr( out_lmul == 2 ) return __riscv_vlmul_trunc_i16m2(a);
      else if constexpr( out_lmul == 4 ) return __riscv_vlmul_trunc_i16m4(a);
    }
    else if constexpr( match(c, category::uint16) )
    {
      if constexpr( out_lmul == -4 ) return __riscv_vlmul_trunc_u16mf4(a);
      else if constexpr( out_lmul == -2 ) return __riscv_vlmul_trunc_u16mf2(a);
      else if constexpr( out_lmul == 1 ) return __riscv_vlmul_trunc_u16m1(a);
      else if constexpr( out_lmul == 2 ) return __riscv_vlmul_trunc_u16m2(a);
      else if constexpr( out_lmul == 4 ) return __riscv_vlmul_trunc_u16m4(a);
    }
    else if constexpr( match(c, category::int8) )
    {
      if constexpr( out_lmul == -8 ) return __riscv_vlmul_trunc_i8mf8(a);
      else if constexpr( out_lmul == -4 ) return __riscv_vlmul_trunc_i8mf4(a);
      else if constexpr( out_lmul == -2 ) return __riscv_vlmul_trunc_i8mf2(a);
      else if constexpr( out_lmul == 1 ) return __riscv_vlmul_trunc_i8m1(a);
      else if constexpr( out_lmul == 2 ) return __riscv_vlmul_trunc_i8m2(a);
      else if constexpr( out_lmul == 4 ) return __riscv_vlmul_trunc_i8m4(a);
    }
    else if constexpr( match(c, category::uint8) )
    {
      if constexpr( out_lmul == -8 ) return __riscv_vlmul_trunc_u8mf8(a);
      else if constexpr( out_lmul == -4 ) return __riscv_vlmul_trunc_u8mf4(a);
      else if constexpr( out_lmul == -2 ) return __riscv_vlmul_trunc_u8mf2(a);
      else if constexpr( out_lmul == 1 ) return __riscv_vlmul_trunc_u8m1(a);
      else if constexpr( out_lmul == 2 ) return __riscv_vlmul_trunc_u8m2(a);
      else if constexpr( out_lmul == 4 ) return __riscv_vlmul_trunc_u8m4(a);
    }
  }
}

//================================================================================================
// Single slice
//================================================================================================

template<typename T, typename N>
EVE_FORCEINLINE wide<T, typename N::split_type>
                slice(wide<T, N> a, lower_slice_t) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto in_lmul  = riscv_rvv_dyn_::getLMUL<T>(N::value);
  constexpr auto out_lmul = riscv_rvv_dyn_::getLMUL<T>(N::split_type::value);
  if constexpr( in_lmul == out_lmul ) return a.storage();
  else
  {
    // we need to lower lmul - call lmul trunc.
    return riscv_lmul_trunc(a);
  }
}

template<typename T, typename N>
EVE_FORCEINLINE wide<T, typename N::split_type>
                slice(wide<T, N> a, upper_slice_t) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto shift_size = N::split_type::value;
  wide<T, N>     res        = __riscv_vslidedown(a, shift_size, N::value);
  constexpr auto in_lmul    = riscv_rvv_dyn_::getLMUL<T>(N::value);
  constexpr auto out_lmul   = riscv_rvv_dyn_::getLMUL<T>(N::split_type::value);
  if constexpr( in_lmul == out_lmul ) return res.storage();
  else
  {
    // we need to lower lmul - call lmul trunc.
    return riscv_lmul_trunc(res);
  }
}

template<typename T, typename N>
EVE_FORCEINLINE logical<wide<T, typename N::split_type>>
                slice(logical<wide<T, N>> a, lower_slice_t) noexcept
requires rvv_abi<abi_t<T, N>>
{
  return bit_cast(a, as<logical<wide<T, typename N::split_type>>> {});
}

template<typename T, typename N>
EVE_FORCEINLINE logical<wide<T, typename N::split_type>>
                slice(logical<wide<T, N>> a, upper_slice_t) noexcept
requires rvv_abi<abi_t<T, N>>
{
  auto bits_slice = a.bits().slice(upper_slice_t {});

  logical<wide<as_integer_t<T, unsigned>, typename N::split_type>> neq = bits_slice != 0;
  return bit_cast(neq, as<logical<wide<T, typename N::split_type>>> {});
}

//================================================================================================
// Both slice
//================================================================================================
template<typename T, typename N>
EVE_FORCEINLINE auto
slice(wide<T, N> a) noexcept
requires rvv_abi<abi_t<T, N>>
{
  std::array<wide<T, typename N::split_type>, 2> that {slice(a, lower_), slice(a, upper_)};
  return that;
}

template<typename T, typename N>
EVE_FORCEINLINE auto
slice(logical<wide<T, N>> a) noexcept
requires rvv_abi<abi_t<T, N>>
{
  logical<wide<T, typename N::split_type>> lower = slice(a, lower_);
  logical<wide<T, typename N::split_type>> upper = slice(a, upper_);

  std::array<logical<wide<T, typename N::split_type>>, 2> that {lower, upper};
  return that;
}

}
