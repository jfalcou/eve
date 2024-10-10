//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/riscv/rvv_utils.hpp>
#include <eve/arch/wide.hpp>

namespace eve::detail
{
// Logical-wide conversions.
// For interal utils for RVV, not expected to be used outsize of this file.
// Needed as for casting between logical-logical with different N,
// as RISC-V needs to have an intermediate vector register type.
// These functions cast logical to wide or wide to logical.
// No additional work (e.g. filling with zeros undefined bits) is expected.
template<scalar_value T, typename N, scalar_value U, typename M>
EVE_FORCEINLINE logical<wide<U, M>>
                rvv_simd_cast(wide<T, N> x, as<logical<wide<U, M>>> const                &tgt) noexcept
requires rvv_abi<abi_t<T, N>> && rvv_abi<abi_t<U, M>>
{
  constexpr auto in_lmul = rvv_lmul_v<T, N>;
  if constexpr( in_lmul != 1 )
  {
    static_assert(
        in_lmul == 1,
        "[riscv eve] sanity check. Can not cast wide to logical for not m1 vector register");
  }
  else if constexpr( std::is_floating_point_v<T> )
    return simd_cast(simd_cast(x, as<wide<as_integer_t<T>, N>> {}), tgt);
  else
  {
    static_assert(in_lmul == 1, "[riscv eve] Can not bitcast to logical not m1 vector register");
    constexpr auto out_lmul = rvv_lmul_v<U, M>;
    constexpr auto size     = sizeof(U) * 8;
    constexpr auto bit_size = out_lmul > 0 ? size / out_lmul : size * (-out_lmul);
    if constexpr( bit_size == 1 ) return __riscv_vreinterpret_b1(x);
    else if constexpr( bit_size == 2 ) return __riscv_vreinterpret_b2(x);
    else if constexpr( bit_size == 4 ) return __riscv_vreinterpret_b4(x);
    else if constexpr( bit_size == 8 ) return __riscv_vreinterpret_b8(x);
    else if constexpr( bit_size == 16 ) return __riscv_vreinterpret_b16(x);
    else if constexpr( bit_size == 32 ) return __riscv_vreinterpret_b32(x);
    else if constexpr( bit_size == 64 ) return __riscv_vreinterpret_b64(x);
  }
}

template<scalar_value T, typename N, scalar_value U, typename M>
EVE_FORCEINLINE wide<U, M>
                rvv_simd_cast(logical<wide<T, N>> x, as<wide<U, M>>) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto out_lmul = rvv_lmul_v<U, M>;
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

// logical-logical - with logical-wide-logical.
// it is expected that it could be called with different N/M
// * N >= M: when we have is_full false, we first work with full_type, that bitcast it to smaller
// type.
// * N < M: is_full false, we could cast from not full type to full one.
template<callable_options O, scalar_value T, typename N, scalar_value U, typename M>
EVE_FORCEINLINE logical<wide<U, M>>
                simd_cast_(EVE_REQUIRES(rvv_),
                           const O&,
                           logical<wide<T, N>>            x,
                           as<logical<wide<U, M>>> const                &tgt) noexcept
requires(rvv_abi<abi_t<T, N>> && rvv_abi<abi_t<U, M>>)
{
  using part_type_cast = detail::rvv_m1_wide<std::uint32_t>;
  auto u_casted_in     = rvv_simd_cast(x, as<part_type_cast> {});
  auto to_ret          = rvv_simd_cast(u_casted_in, tgt);
  return to_ret;
}

template<typename N, typename M>
EVE_FORCEINLINE wide<std::int8_t, M>
                rvv_lmul_trunc(wide<std::int8_t, N> a, as<wide<std::int8_t, M>>) noexcept
requires rvv_abi<abi_t<std::int8_t, N>>
{
  using out_wide_t        = wide<std::int8_t, M>;
  constexpr auto out_lmul = rvv_lmul_v<std::int8_t, M>;
  if constexpr( out_lmul == -8 ) return __riscv_vlmul_trunc_i8mf8(a);
  else if constexpr( out_lmul == -4 ) return __riscv_vlmul_trunc_i8mf4(a);
  else if constexpr( out_lmul == -2 ) return __riscv_vlmul_trunc_i8mf2(a);
  else if constexpr( out_lmul == 1 ) return __riscv_vlmul_trunc_i8m1(a);
  else if constexpr( out_lmul == 2 ) return __riscv_vlmul_trunc_i8m2(a);
  else if constexpr( out_lmul == 4 ) return __riscv_vlmul_trunc_i8m4(a);
}

template<typename N, typename M>
EVE_FORCEINLINE wide<std::int8_t, M>
                rvv_lmul_extend(wide<std::int8_t, N> a, as<wide<std::int8_t, M>>) noexcept
requires(rvv_abi<abi_t<std::int8_t, N>> && rvv_abi<abi_t<std::int8_t, M>>)
{
  using out_wide_t        = wide<std::int8_t, M>;
  constexpr auto out_lmul = rvv_lmul_v<std::int8_t, M>;
  if constexpr( out_lmul == -4 ) return __riscv_vlmul_ext_i8mf4(a);
  else if constexpr( out_lmul == -2 ) return __riscv_vlmul_ext_i8mf2(a);
  else if constexpr( out_lmul == 1 ) return __riscv_vlmul_ext_i8m1(a);
  else if constexpr( out_lmul == 2 ) return __riscv_vlmul_ext_i8m2(a);
  else if constexpr( out_lmul == 4 ) return __riscv_vlmul_ext_i8m4(a);
  else if constexpr( out_lmul == 8 ) return __riscv_vlmul_ext_i8m8(a);
}

template<callable_options O, arithmetic_simd_value In, arithmetic_simd_value Out>
EVE_FORCEINLINE Out
simd_cast_(EVE_REQUIRES(rvv_), const O&, In x, as<Out> const& tgt) noexcept
requires(rvv_abi<typename In::abi_type> && rvv_abi<typename Out::abi_type>)
{
  // Represents a wide that occupies the same size, but formed with int8_t.
  // Here we use that sizeof(std::int8_t) == 1, so sizeof(In) will represent the number
  // of std::int8_t, that are needed to have the same size.
  using i8_in_t  = wide<std::int8_t, fixed<sizeof(In)>>;
  using i8_tgt_t = wide<std::int8_t, fixed<sizeof(Out)>>;
  if constexpr( sizeof(In) == sizeof(Out) ) return bit_cast(x, tgt);
  else if constexpr( sizeof(In) < sizeof(Out) )
  {
    auto i8_x     = bit_cast(x, as<i8_in_t> {});
    auto x_extend = rvv_lmul_extend(i8_x, as<i8_tgt_t> {});
    return bit_cast(x_extend, tgt);
  }
  else
  {
    auto i8_x    = bit_cast(x, as<i8_in_t> {});
    auto x_trunc = rvv_lmul_trunc(i8_x, as<i8_tgt_t> {});
    return bit_cast(x_trunc, tgt);
  }
}
}
