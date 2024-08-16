//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/simd.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/traits/as_integer.hpp>

namespace eve::detail
{
template<plain_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, typename N::combined_type>
                riscv_lmul_ext(wide<T, N> a) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, typename N::combined_type>>();
  static_assert(N::combined_type::value != N::value);
  constexpr auto in_lmul  = riscv_rvv_dyn_::getLMUL<T>(N::value);
  constexpr auto out_lmul = riscv_rvv_dyn_::getLMUL<T>(N::combined_type::value);
  if constexpr( out_lmul == in_lmul ) return a.storage();
  else if constexpr( match(c, category::float64) )
  {
    if constexpr( out_lmul == 2 ) return __riscv_vlmul_ext_f64m2(a);
    else if constexpr( out_lmul == 4 ) return __riscv_vlmul_ext_f64m4(a);
    else if constexpr( out_lmul == 8 ) return __riscv_vlmul_ext_f64m8(a);
  }
  else if constexpr( match(c, category::int64) )
  {
    if constexpr( out_lmul == 2 ) return __riscv_vlmul_ext_i64m2(a);
    else if constexpr( out_lmul == 4 ) return __riscv_vlmul_ext_i64m4(a);
    else if constexpr( out_lmul == 8 ) return __riscv_vlmul_ext_i64m8(a);
  }
  else if constexpr( match(c, category::uint64) )
  {
    if constexpr( out_lmul == 2 ) return __riscv_vlmul_ext_u64m2(a);
    else if constexpr( out_lmul == 4 ) return __riscv_vlmul_ext_u64m4(a);
    else if constexpr( out_lmul == 8 ) return __riscv_vlmul_ext_u64m8(a);
  }
  else if constexpr( match(c, category::float32) )
  {
    if constexpr( out_lmul == 1 ) return __riscv_vlmul_ext_f32m1(a);
    else if constexpr( out_lmul == 2 ) return __riscv_vlmul_ext_f32m2(a);
    else if constexpr( out_lmul == 4 ) return __riscv_vlmul_ext_f32m4(a);
    else if constexpr( out_lmul == 8 ) return __riscv_vlmul_ext_f32m8(a);
  }
  else if constexpr( match(c, category::int32) )
  {
    if constexpr( out_lmul == 1 ) return __riscv_vlmul_ext_i32m1(a);
    else if constexpr( out_lmul == 2 ) return __riscv_vlmul_ext_i32m2(a);
    else if constexpr( out_lmul == 4 ) return __riscv_vlmul_ext_i32m4(a);
    else if constexpr( out_lmul == 8 ) return __riscv_vlmul_ext_i32m8(a);
  }
  else if constexpr( match(c, category::uint32) )
  {
    if constexpr( out_lmul == 1 ) return __riscv_vlmul_ext_u32m1(a);
    else if constexpr( out_lmul == 2 ) return __riscv_vlmul_ext_u32m2(a);
    else if constexpr( out_lmul == 4 ) return __riscv_vlmul_ext_u32m4(a);
    else if constexpr( out_lmul == 8 ) return __riscv_vlmul_ext_u32m8(a);
  }
  else if constexpr( match(c, category::int16) )
  {
    if constexpr( out_lmul == -2 ) return __riscv_vlmul_ext_i16mf2(a);
    else if constexpr( out_lmul == 1 ) return __riscv_vlmul_ext_i16m1(a);
    else if constexpr( out_lmul == 2 ) return __riscv_vlmul_ext_i16m2(a);
    else if constexpr( out_lmul == 4 ) return __riscv_vlmul_ext_i16m4(a);
    else if constexpr( out_lmul == 8 ) return __riscv_vlmul_ext_i16m8(a);
  }
  else if constexpr( match(c, category::uint16) )
  {
    if constexpr( out_lmul == -2 ) return __riscv_vlmul_ext_u16mf2(a);
    else if constexpr( out_lmul == 1 ) return __riscv_vlmul_ext_u16m1(a);
    else if constexpr( out_lmul == 2 ) return __riscv_vlmul_ext_u16m2(a);
    else if constexpr( out_lmul == 4 ) return __riscv_vlmul_ext_u16m4(a);
    else if constexpr( out_lmul == 8 ) return __riscv_vlmul_ext_u16m8(a);
  }
  else if constexpr( match(c, category::int8) )
  {
    if constexpr( out_lmul == -4 ) return __riscv_vlmul_ext_i8mf4(a);
    else if constexpr( out_lmul == -2 ) return __riscv_vlmul_ext_i8mf2(a);
    else if constexpr( out_lmul == 1 ) return __riscv_vlmul_ext_i8m1(a);
    else if constexpr( out_lmul == 2 ) return __riscv_vlmul_ext_i8m2(a);
    else if constexpr( out_lmul == 4 ) return __riscv_vlmul_ext_i8m4(a);
    else if constexpr( out_lmul == 8 ) return __riscv_vlmul_ext_i8m8(a);
  }
  else if constexpr( match(c, category::uint8) )
  {
    if constexpr( out_lmul == -4 ) return __riscv_vlmul_ext_u8mf4(a);
    else if constexpr( out_lmul == -2 ) return __riscv_vlmul_ext_u8mf2(a);
    else if constexpr( out_lmul == 1 ) return __riscv_vlmul_ext_u8m1(a);
    else if constexpr( out_lmul == 2 ) return __riscv_vlmul_ext_u8m2(a);
    else if constexpr( out_lmul == 4 ) return __riscv_vlmul_ext_u8m4(a);
    else if constexpr( out_lmul == 8 ) return __riscv_vlmul_ext_u8m8(a);
  }
}

template<typename T, typename N, typename U, typename M>
concept same_wide_size = sizeof(wide<T, N>) == sizeof(wide<U, M>);

template<typename T, typename N, typename U, typename M>
concept same_raw_wide_size = sizeof(T) *
N::value == sizeof(U) * M::value;

template<typename T, typename U>
concept same_element_size = sizeof(T) == sizeof(U);

template<typename T, typename U>
concept different_type = !
std::is_same_v<T, U>;

template<typename T, typename N, typename U, typename M>
concept same_type_types = (match(categorize<wide<T, N>>(), category::int_)
                           && match(categorize<wide<U, M>>(), category::int_))
                          || (match(categorize<wide<T, N>>(), category::uint_)
                              && match(categorize<wide<U, M>>(), category::uint_))
                          || (match(categorize<wide<T, N>>(), category::float_)
                              && match(categorize<wide<U, M>>(), category::float_));

template<callable_options O, scalar_value T, typename N, scalar_value U>
EVE_FORCEINLINE wide<U, N>
bit_cast_(EVE_REQUIRES(rvv_), O const&, const wide<T, N>& x, as<wide<U, N>> const&) noexcept
requires rvv_abi<abi_t<T, N>> && rvv_abi<abi_t<U, N>> && same_wide_size<T, N, U, N>
         && same_element_size<T, U> && different_type<T, U>
         && (sizeof(T) * N::value == sizeof(U) * N::value)
{
  using out_wide          = wide<U, N>;
  constexpr auto out_c    = categorize<out_wide>();
  constexpr auto out_lmul = riscv_rvv_dyn_::getLMUL<U>(N::value);
  if constexpr( match(out_c, category::float64) )
  {
    if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_f64m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_f64m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_f64m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_f64m8(x);
  }
  else if constexpr( match(out_c, category::int64) )
  {
    if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_i64m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_i64m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_i64m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_i64m8(x);
  }
  else if constexpr( match(out_c, category::uint64) )
  {
    if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_u64m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_u64m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_u64m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_u64m8(x);
  }
  else if constexpr( match(out_c, category::float32) )
  {
    if constexpr( out_lmul == -2 ) return __riscv_vreinterpret_f32mf2(x);
    else if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_f32m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_f32m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_f32m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_f32m8(x);
  }
  else if constexpr( match(out_c, category::int32) )
  {
    if constexpr( out_lmul == -2 ) return __riscv_vreinterpret_i32mf2(x);
    else if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_i32m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_i32m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_i32m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_i32m8(x);
  }
  else if constexpr( match(out_c, category::uint32) )
  {
    if constexpr( out_lmul == -2 ) return __riscv_vreinterpret_u32mf2(x);
    else if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_u32m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_u32m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_u32m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_u32m8(x);
  }
  else if constexpr( match(out_c, category::int16) )
  {
    if constexpr( out_lmul == -4 ) return __riscv_vreinterpret_i16mf4(x);
    else if constexpr( out_lmul == -2 ) return __riscv_vreinterpret_i16mf2(x);
    else if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_i16m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_i16m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_i16m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_i16m8(x);
  }
  else if constexpr( match(out_c, category::uint16) )
  {
    if constexpr( out_lmul == -4 ) return __riscv_vreinterpret_u16mf4(x);
    else if constexpr( out_lmul == -2 ) return __riscv_vreinterpret_u16mf2(x);
    else if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_u16m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_u16m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_u16m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_u16m8(x);
  }
  else if constexpr( match(out_c, category::int8) )
  {
    if constexpr( out_lmul == -8 ) return __riscv_vreinterpret_i8mf8(x);
    else if constexpr( out_lmul == -4 ) return __riscv_vreinterpret_i8mf4(x);
    else if constexpr( out_lmul == -2 ) return __riscv_vreinterpret_i8mf2(x);
    else if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_i8m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_i8m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_i8m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_i8m8(x);
  }
  else if constexpr( match(out_c, category::uint8) )
  {
    if constexpr( out_lmul == -8 ) return __riscv_vreinterpret_u8mf8(x);
    else if constexpr( out_lmul == -4 ) return __riscv_vreinterpret_u8mf4(x);
    else if constexpr( out_lmul == -2 ) return __riscv_vreinterpret_u8mf2(x);
    else if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_u8m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_u8m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_u8m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_u8m8(x);
  }
}

// change sew only.
template<callable_options O, scalar_value T, typename N, scalar_value U, typename M>
EVE_FORCEINLINE wide<U, M>
bit_cast_(EVE_REQUIRES(rvv_), const O&, const wide<T, N>& x, as<wide<U, M>> const&) noexcept
requires rvv_abi<abi_t<T, N>> && rvv_abi<abi_t<U, M>> && same_wide_size<T, N, U, M>
         && (!same_element_size<T, U>) && same_type_types<T, N, U, M>
         && same_raw_wide_size<T, N, U, M>
{
  using in_wide           = wide<T, N>;
  using out_wide          = wide<U, M>;
  constexpr auto out_lmul = riscv_rvv_dyn_::getLMUL<U>(M::value);

  constexpr auto in_c  = categorize<in_wide>();
  constexpr auto out_c = categorize<out_wide>();

  if constexpr( match(out_c, category::int8) )
  {
    if constexpr( out_lmul == -8 ) return __riscv_vreinterpret_i8mf8(x);
    else if constexpr( out_lmul == -4 ) return __riscv_vreinterpret_i8mf4(x);
    else if constexpr( out_lmul == -2 ) return __riscv_vreinterpret_i8mf2(x);
    else if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_i8m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_i8m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_i8m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_i8m8(x);
  }
  else if constexpr( match(out_c, category::uint8) )
  {
    if constexpr( out_lmul == -8 ) return __riscv_vreinterpret_u8mf8(x);
    else if constexpr( out_lmul == -4 ) return __riscv_vreinterpret_u8mf4(x);
    else if constexpr( out_lmul == -2 ) return __riscv_vreinterpret_u8mf2(x);
    else if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_u8m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_u8m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_u8m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_u8m8(x);
  }
  else if constexpr( match(out_c, category::int16) )
  {
    if constexpr( out_lmul == -4 ) return __riscv_vreinterpret_i16mf4(x);
    else if constexpr( out_lmul == -2 ) return __riscv_vreinterpret_i16mf2(x);
    else if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_i16m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_i16m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_i16m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_i16m8(x);
  }
  else if constexpr( match(out_c, category::uint16) )
  {
    if constexpr( out_lmul == -4 ) return __riscv_vreinterpret_u16mf4(x);
    else if constexpr( out_lmul == -2 ) return __riscv_vreinterpret_u16mf2(x);
    else if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_u16m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_u16m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_u16m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_u16m8(x);
  }
  else if constexpr( match(out_c, category::int32) )
  {
    if constexpr( out_lmul == -2 ) return __riscv_vreinterpret_i32mf2(x);
    else if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_i32m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_i32m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_i32m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_i32m8(x);
  }
  else if constexpr( match(out_c, category::uint32) )
  {
    if constexpr( out_lmul == -2 ) return __riscv_vreinterpret_u32mf2(x);
    else if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_u32m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_u32m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_u32m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_u32m8(x);
  }
  else if constexpr( match(out_c, category::float32) )
  {
    if constexpr( out_lmul == -2 )
    {
      auto casted_to_32 = bit_cast(x, as<wide<std::int32_t, M>> {});
      return __riscv_vreinterpret_f32mf2(casted_to_32);
    }
    else if constexpr( out_lmul == 1 )
    {
      auto casted_to_32 = bit_cast(x, as<wide<std::int32_t, M>> {});
      return __riscv_vreinterpret_f32m1(casted_to_32);
    }
    else if constexpr( out_lmul == 2 )
    {
      auto casted_to_32 = bit_cast(x, as<wide<std::int32_t, M>> {});
      return __riscv_vreinterpret_f32m2(casted_to_32);
    }
    else if constexpr( out_lmul == 4 )
    {
      auto casted_to_32 = bit_cast(x, as<wide<std::int32_t, M>> {});
      return __riscv_vreinterpret_f32m4(casted_to_32);
    }
    else if constexpr( out_lmul == 8 )
    {
      auto casted_to_32 = bit_cast(x, as<wide<std::int32_t, M>> {});
      return __riscv_vreinterpret_f32m8(casted_to_32);
    }
  }
  else if constexpr( match(out_c, category::int64) )
  {
    if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_i64m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_i64m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_i64m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_i64m8(x);
  }
  else if constexpr( match(out_c, category::uint64) )
  {
    if constexpr( out_lmul == 1 ) return __riscv_vreinterpret_u64m1(x);
    else if constexpr( out_lmul == 2 ) return __riscv_vreinterpret_u64m2(x);
    else if constexpr( out_lmul == 4 ) return __riscv_vreinterpret_u64m4(x);
    else if constexpr( out_lmul == 8 ) return __riscv_vreinterpret_u64m8(x);
  }
  if constexpr( match(out_c, category::float64) )
  {
    if constexpr( out_lmul == 1 )
    {
      auto casted_to_64 = bit_cast(x, as<wide<std::int64_t, M>> {});
      return __riscv_vreinterpret_f64m1(casted_to_64);
    }
    else if constexpr( out_lmul == 2 )
    {
      auto casted_to_64 = bit_cast(x, as<wide<std::int64_t, M>> {});
      return __riscv_vreinterpret_f64m2(casted_to_64);
    }
    else if constexpr( out_lmul == 4 )
    {
      auto casted_to_64 = bit_cast(x, as<wide<std::int64_t, M>> {});
      return __riscv_vreinterpret_f64m4(casted_to_64);
    }
    else if constexpr( out_lmul == 8 )
    {
      auto casted_to_64 = bit_cast(x, as<wide<std::int64_t, M>> {});
      return __riscv_vreinterpret_f64m8(casted_to_64);
    }
  }
}

template<callable_options O, scalar_value T, typename N, scalar_value U, typename M>
EVE_FORCEINLINE wide<U, M>
                bit_cast_(EVE_REQUIRES(rvv_),
                          const O&,
                          const kumi::tuple<eve::wide<T, N>>                &x,
                          as<wide<U, M>> const                              &to_as) noexcept
requires rvv_abi<abi_t<T, N>> && rvv_abi<abi_t<U, M>>
{
  return bit_cast(get<0>(x), to_as);
}

template<callable_options O, scalar_value T, typename N, scalar_value U, typename M>
EVE_FORCEINLINE auto
bit_cast_(EVE_REQUIRES(rvv_),
          const O&,
          const kumi::tuple<logical<eve::wide<T, N>>>& x,
          as<logical<wide<U, M>>> const              & to_as) noexcept
requires rvv_abi<abi_t<T, N>> && rvv_abi<abi_t<U, M>>
{
  return bit_cast(get<0>(x), to_as);
}

template<callable_options O, scalar_value T, typename N, scalar_value U, typename M>
EVE_FORCEINLINE wide<U, M>
bit_cast_(EVE_REQUIRES(rvv_), const O&, const wide<T, N>& x, as<wide<U, M>> const& to_as) noexcept
requires rvv_abi<abi_t<T, N>> && rvv_abi<abi_t<U, M>> && same_wide_size<T, N, U, M>
         && same_raw_wide_size<T, N, U, M>
{
  using in_wide  = wide<T, N>;
  using out_wide = wide<U, M>;

  constexpr auto in_c  = categorize<in_wide>();
  constexpr auto out_c = categorize<out_wide>();

  if constexpr( match(in_c, category::float_) )
  {
    //  float. We need cast to the to intype with the same width.
    using sign            = default_as_integer_sign_t<U>;
    using out_part_scalar = as_integer_t<T, sign>;
    using out_part_wide   = wide<out_part_scalar, N>;
    auto part_done        = bit_cast(x, as<out_part_wide> {});

    return bit_cast(part_done, to_as);
  }
  else
  {
    // first change sew, then cast to type
    using sign            = default_as_integer_sign_t<T>;
    using out_part_scalar = as_integer_t<U, sign>;
    using out_part_wide   = wide<out_part_scalar, M>;
    auto part_done        = bit_cast(x, as<out_part_wide> {});
    return bit_cast(part_done, to_as);
  }
}

// we need to fill other values by zero
template<callable_options O, scalar_value T, typename N, scalar_value U, typename M>
EVE_FORCEINLINE wide<U, M>
bit_cast_(EVE_REQUIRES(rvv_), const O&, const wide<T, N>& x, as<wide<U, M>> const& to_as) noexcept
requires(!same_wide_size<T, N, U, M>) && rvv_abi<abi_t<T, N>> && rvv_abi<abi_t<U, M>>
{
  constexpr size_t in_size  = sizeof(wide<T, N>);
  constexpr size_t out_size = sizeof(wide<U, M>);
  constexpr auto   in_lmul  = riscv_rvv_dyn_::getLMUL<T>(N::value);
  constexpr auto   out_lmul = riscv_rvv_dyn_::getLMUL<U>(M::value);
  if constexpr( in_lmul < out_lmul )
  {
    static_assert(in_size < out_size);
    // extend lmul and go again
    // out lmul > in_lmul
    auto extended_input = riscv_lmul_ext(x);
    for( auto id = N::value; id < N::combined_type::value; ++id )
    {
      extended_input.set(id, static_cast<T>(0));
    }
    auto to_ret = bit_cast(extended_input, to_as);
    return to_ret;
  }
  else
  {
    static_assert(in_lmul != out_lmul);
    static_assert(in_size > out_size);
    // in_lmul > out_lmul
    auto bigger_cast = bit_cast(x, as<wide<U, typename M::combined_type>> {});
    return riscv_lmul_trunc(bigger_cast);
  }
}

// Logical-wide conversions.
template<callable_options O, scalar_value T, typename N, scalar_value U, typename M>
EVE_FORCEINLINE logical<wide<U, M>>
                bit_cast_(EVE_REQUIRES(rvv_),
                          const O&,
                          const wide<T, N>                             &x,
                          as<logical<wide<U, M>>> const                &tgt) noexcept
requires rvv_abi<abi_t<T, N>> && rvv_abi<abi_t<U, M>>
{
  constexpr auto in_lmul = riscv_rvv_dyn_::getLMUL<T>(N::value);
  if constexpr( in_lmul > 1 ) return bit_cast(riscv_lmul_trunc(x), tgt);
  else if constexpr( in_lmul < 0 )
  {
    auto extended_in = bit_cast(x, as<wide<T, typename N::combined_type>> {});
    return bit_cast(extended_in, tgt);
  }
  else if constexpr( std::is_floating_point_v<T> )
    return bit_cast(bit_cast(x, as<wide<as_integer_t<T>, N>> {}), tgt);
  else
  {
    static_assert(in_lmul == 1, "[riscv eve] Can not bitcast to logical not m1 vector register");
    constexpr auto out_lmul = riscv_rvv_dyn_::getLMUL<U>(M::value);
    constexpr auto size     = sizeof(U) * 8;
    constexpr auto bit_size = out_lmul > 0 ? size / out_lmul : size * (-out_lmul);
    if constexpr( bit_size == 1 ) return __riscv_vreinterpret_b1(x);
    if constexpr( bit_size == 2 ) return __riscv_vreinterpret_b2(x);
    if constexpr( bit_size == 4 ) return __riscv_vreinterpret_b4(x);
    if constexpr( bit_size == 8 ) return __riscv_vreinterpret_b8(x);
    if constexpr( bit_size == 16 ) return __riscv_vreinterpret_b16(x);
    if constexpr( bit_size == 32 ) return __riscv_vreinterpret_b32(x);
    if constexpr( bit_size == 64 ) return __riscv_vreinterpret_b64(x);
  }
}

template<callable_options O, scalar_value T, typename N, scalar_value U, typename M>
EVE_FORCEINLINE wide<U, M>
                bit_cast_(EVE_REQUIRES(rvv_),
                          const O&,
                          const logical<wide<T, N>>                &x,
                          as<wide<U, M>> const&) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto out_lmul = riscv_rvv_dyn_::getLMUL<U>(M::value);
  static_assert(out_lmul == 1,
                "[riscv eve] Can not bitcast from logical not to m1 vector register");
  constexpr auto c = categorize<wide<U, M>>();
  if constexpr( match(c, category::int64) ) return __riscv_vreinterpret_i64m1(x);
  else if constexpr( match(c, category::uint64) ) return __riscv_vreinterpret_u64m1(x);
  else if constexpr( match(c, category::int32) ) return __riscv_vreinterpret_i32m1(x);
  else if constexpr( match(c, category::uint32) ) return __riscv_vreinterpret_u32m1(x);
  else if constexpr( match(c, category::int16) ) return __riscv_vreinterpret_i16m1(x);
  else if constexpr( match(c, category::uint16) ) return __riscv_vreinterpret_u16m1(x);
  else if constexpr( match(c, category::int8) ) return __riscv_vreinterpret_i8m1(x);
  else if constexpr( match(c, category::uint8) ) return __riscv_vreinterpret_u8m1(x);
  else if constexpr( match(c, category::float32) )
    return __riscv_vreinterpret_f32m1(__riscv_vreinterpret_u32m1(x));
  else if constexpr( match(c, category::float64) )
    return __riscv_vreinterpret_f64m1(__riscv_vreinterpret_u64m1(x));
}

// logical-logical - with logical-wide-logical
template<callable_options O, scalar_value T, typename N, scalar_value U, typename M>
EVE_FORCEINLINE logical<wide<U, M>>
                bit_cast_(EVE_REQUIRES(rvv_),
                          const O&,
                          const logical<wide<T, N>>                    &x,
                          as<logical<wide<U, M>>> const                &tgt) noexcept
requires rvv_abi<abi_t<T, N>> || rvv_abi<abi_t<U, M>>
{
  if constexpr( is_aggregated_v<abi_t<T, N>> || is_aggregated_v<abi_t<U, M>> )
  {
    auto [lv, hv] = x.slice();
    auto half_tgt = as<logical<wide<U, typename M::split_type>>> {};
    auto to_ret   = logical<wide<U, M>> {bit_cast(lv, half_tgt), bit_cast(hv, half_tgt)};
    return to_ret;
  }
  else
  {
    // combine.
    using u_m1_cardinal  = typename riscv_rvv_dyn_::m1_fixed<unsigned>;
    using part_type_cast = wide<unsigned, u_m1_cardinal>;
    auto u_casted_in     = bit_cast(x, as<part_type_cast> {});
    // Note. We can have some bits in unspecified state.
    // And we need to zero them.
    constexpr size_t u_size                     = sizeof(unsigned) * 8;
    constexpr size_t valid_elements             = N::value / u_size;
    constexpr size_t valid_bits_in_last_element = N::value % u_size;
    if constexpr ( constexpr auto element = valid_elements; element < u_m1_cardinal::value )
    {
      auto     part_valid_element = u_casted_in.get(element);
      unsigned Mask               = (1 << (valid_bits_in_last_element)) - 1;
      auto     valid_element      = Mask & part_valid_element;
      u_casted_in.set(element, valid_element);
    }
    for( size_t element = valid_elements + 1; element < u_m1_cardinal::value; ++element )
    {
      u_casted_in.set(element, 0);
    }
    auto to_ret = bit_cast(u_casted_in, tgt);
    return to_ret;
  }
}

// equality.
template<callable_options O, scalar_value T, typename N>
EVE_FORCEINLINE logical<wide<T, N>>
                bit_cast_(EVE_REQUIRES(rvv_),
                          const O&,
                          const logical<wide<T, N>>                &x,
                          as<logical<wide<T, N>>> const&) noexcept
requires rvv_abi<abi_t<T, N>>
{
  return x;
}

template<callable_options O, scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
bit_cast_(EVE_REQUIRES(rvv_), const O&, const wide<T, N>& x, as<wide<T, N>> const& tgt) noexcept
requires rvv_abi<abi_t<T, N>>
{
  return x;
}

}
