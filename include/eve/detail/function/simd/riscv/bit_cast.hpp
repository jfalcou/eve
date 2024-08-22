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
#include <eve/arch/riscv/rvv_utils.hpp>

namespace eve::detail
{

template<typename T, typename N, typename U, typename M>
concept same_storage_size = sizeof(wide<T, N>) == sizeof(wide<U, M>);

template<typename T, typename N, typename U, typename M>
concept same_wide_size = sizeof(T) *
N::value == sizeof(U) * M::value;

template<typename T, typename U>
concept same_element_size = sizeof(T) == sizeof(U);

template<typename T, typename U>
concept different_type = !
std::is_same_v<T, U>;

template<typename T, typename N, typename U, typename M>
concept different_wide_types = different_type<T, U> || N::value !=
M::value;

template<typename T, typename N, typename U, typename M>
concept same_type_types = (match(categorize<wide<T, N>>(), category::int_)
                           && match(categorize<wide<U, M>>(), category::int_))
                          || (match(categorize<wide<T, N>>(), category::uint_)
                              && match(categorize<wide<U, M>>(), category::uint_))
                          || (match(categorize<wide<T, N>>(), category::float_)
                              && match(categorize<wide<U, M>>(), category::float_));

// change type only
// For example:
// int -> unsigned
// float -> int
template<callable_options O, scalar_value T, typename N, scalar_value U>
EVE_FORCEINLINE wide<U, N>
bit_cast_(EVE_REQUIRES(rvv_), O const&, wide<T, N> x, as<wide<U, N>> const&) noexcept
requires rvv_abi<abi_t<T, N>> && rvv_abi<abi_t<U, N>> && same_storage_size<T, N, U, N>
         && same_element_size<T, U> && different_type<T, U> && same_wide_size<T, N, U, N>
{
  using out_wide       = wide<U, N>;
  constexpr auto out_c = categorize<out_wide>();

  constexpr auto out_lmul = detail::rvv_lmul_v<U, N>;
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
// For example:
// unsigned -> unsigned char
// int -> char
template<callable_options O, scalar_value T, typename N, scalar_value U, typename M>
EVE_FORCEINLINE wide<U, M>
bit_cast_(EVE_REQUIRES(rvv_), const O&, wide<T, N> x, as<wide<U, M>> const&) noexcept
requires rvv_abi<abi_t<T, N>> && rvv_abi<abi_t<U, M>> && same_storage_size<T, N, U, M>
         && (!same_element_size<T, U>) && same_type_types<T, N, U, M> && same_wide_size<T, N, U, M>
{
  using in_wide           = wide<T, N>;
  using out_wide          = wide<U, M>;
  constexpr auto out_lmul = rvv_lmul_v<T, M>;

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
bit_cast_(EVE_REQUIRES(rvv_), const O&, wide<T, N> x, as<wide<U, M>> const& to_as) noexcept
requires rvv_abi<abi_t<T, N>> && rvv_abi<abi_t<U, M>> && same_storage_size<T, N, U, M>
         && same_wide_size<T, N, U, M> && different_wide_types<T, N, U, M>
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

}
