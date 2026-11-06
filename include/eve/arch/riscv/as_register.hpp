//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/riscv/predef.hpp>
#include <eve/arch/riscv/rvv_utils.hpp>
#include <eve/concept/vectorizable.hpp>
#include <concepts>
#include <cstddef>

namespace eve::_
{
  // -------------------------------------------------------------------------------------------
  // Fixed-size RVV types
  using fixed_vfloat16m1_t       = vfloat16m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 1)));
  using fixed_vfloat32m1_t       = vfloat32m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 1)));
  using fixed_vfloat64m1_t       = vfloat64m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 1)));
  using fixed_vfloat16m2_t       = vfloat16m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
  using fixed_vfloat32m2_t       = vfloat32m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
  using fixed_vfloat64m2_t       = vfloat64m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
  using fixed_vfloat16m4_t       = vfloat16m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
  using fixed_vfloat32m4_t       = vfloat32m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
  using fixed_vfloat64m4_t       = vfloat64m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
  using fixed_vfloat16m8_t       = vfloat16m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
  using fixed_vfloat32m8_t       = vfloat32m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
  using fixed_vfloat64m8_t       = vfloat64m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
  using fixed_vfloat16mf2_t      = vfloat16mf2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
  using fixed_vfloat32mf2_t      = vfloat32mf2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
  using fixed_vfloat16mf4_t      = vfloat16mf4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 4)));

  using fixed_vint8m1_t          = vint8m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 1)));
  using fixed_vint16m1_t         = vint16m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 1)));
  using fixed_vint32m1_t         = vint32m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 1)));
  using fixed_vint64m1_t         = vint64m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 1)));
  using fixed_vint8m2_t          = vint8m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
  using fixed_vint16m2_t         = vint16m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
  using fixed_vint32m2_t         = vint32m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
  using fixed_vint64m2_t         = vint64m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
  using fixed_vint8m4_t          = vint8m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
  using fixed_vint16m4_t         = vint16m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
  using fixed_vint32m4_t         = vint32m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
  using fixed_vint64m4_t         = vint64m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
  using fixed_vint8m8_t          = vint8m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
  using fixed_vint16m8_t         = vint16m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
  using fixed_vint32m8_t         = vint32m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
  using fixed_vint64m8_t         = vint64m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
  using fixed_vint8mf2_t         = vint8mf2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
  using fixed_vint16mf2_t        = vint16mf2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
  using fixed_vint32mf2_t        = vint32mf2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
  using fixed_vint8mf4_t         = vint8mf4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 4)));
  using fixed_vint16mf4_t        = vint16mf4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 4)));
  using fixed_vint8mf8_t         = vint8mf8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 8)));

  using fixed_vuint8m1_t         = vuint8m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 1)));
  using fixed_vuint16m1_t        = vuint16m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 1)));
  using fixed_vuint32m1_t        = vuint32m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 1)));
  using fixed_vuint64m1_t        = vuint64m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 1)));
  using fixed_vuint8m2_t         = vuint8m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
  using fixed_vuint16m2_t        = vuint16m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
  using fixed_vuint32m2_t        = vuint32m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
  using fixed_vuint64m2_t        = vuint64m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
  using fixed_vuint8m4_t         = vuint8m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
  using fixed_vuint16m4_t        = vuint16m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
  using fixed_vuint32m4_t        = vuint32m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
  using fixed_vuint64m4_t        = vuint64m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
  using fixed_vuint8m8_t         = vuint8m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
  using fixed_vuint16m8_t        = vuint16m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
  using fixed_vuint32m8_t        = vuint32m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
  using fixed_vuint64m8_t        = vuint64m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
  using fixed_vuint8mf2_t        = vuint8mf2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
  using fixed_vuint16mf2_t       = vuint16mf2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
  using fixed_vuint32mf2_t       = vuint32mf2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
  using fixed_vuint8mf4_t        = vuint8mf4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 4)));
  using fixed_vuint16mf4_t       = vuint16mf4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 4)));
  using fixed_vuint8mf8_t        = vuint8mf8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 8)));

  using fixed_vbool1_t           = vbool1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 1)));
  using fixed_vbool2_t           = vbool2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
  using fixed_vbool4_t           = vbool4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 4)));
  using fixed_vbool8_t           = vbool8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 8)));
  using fixed_vbool16_t          = vbool16_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 16)));
  using fixed_vbool32_t          = vbool32_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 32)));
  using fixed_vbool64_t          = vbool64_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 64)));

  // Fails with a readable message as soon as an unsupported register is actually required
  template<typename T, auto... Keys>
  struct no_rvv_register
  {
    static_assert(sizeof(T) == 0, "[eve riscv] Type is not usable in SIMD register");
  };

  // ---------------------------------------------------------------------------------------------
  // RVV register: Negative LMUL stands for fractional (-2 = mf2)
  template<typename T, std::size_t Bits, int LMul>
  extern _::no_rvv_register<T, Bits, LMul> rvv_register;

  template<floating_scalar_value T> extern _::fixed_vfloat16m1_t       rvv_register<T, 16,  1>;
  template<floating_scalar_value T> extern _::fixed_vfloat32m1_t       rvv_register<T, 32,  1>;
  template<floating_scalar_value T> extern _::fixed_vfloat64m1_t       rvv_register<T, 64,  1>;
  template<floating_scalar_value T> extern _::fixed_vfloat16m2_t       rvv_register<T, 16,  2>;
  template<floating_scalar_value T> extern _::fixed_vfloat32m2_t       rvv_register<T, 32,  2>;
  template<floating_scalar_value T> extern _::fixed_vfloat64m2_t       rvv_register<T, 64,  2>;
  template<floating_scalar_value T> extern _::fixed_vfloat16m4_t       rvv_register<T, 16,  4>;
  template<floating_scalar_value T> extern _::fixed_vfloat32m4_t       rvv_register<T, 32,  4>;
  template<floating_scalar_value T> extern _::fixed_vfloat64m4_t       rvv_register<T, 64,  4>;
  template<floating_scalar_value T> extern _::fixed_vfloat16m8_t       rvv_register<T, 16,  8>;
  template<floating_scalar_value T> extern _::fixed_vfloat32m8_t       rvv_register<T, 32,  8>;
  template<floating_scalar_value T> extern _::fixed_vfloat64m8_t       rvv_register<T, 64,  8>;
  template<floating_scalar_value T> extern _::fixed_vfloat16mf2_t      rvv_register<T, 16, -2>;
  template<floating_scalar_value T> extern _::fixed_vfloat32mf2_t      rvv_register<T, 32, -2>;
  template<floating_scalar_value T> extern _::fixed_vfloat16mf4_t      rvv_register<T, 16, -4>;

  template<std::signed_integral T> extern _::fixed_vint8m1_t          rvv_register<T,  8,  1>;
  template<std::signed_integral T> extern _::fixed_vint16m1_t         rvv_register<T, 16,  1>;
  template<std::signed_integral T> extern _::fixed_vint32m1_t         rvv_register<T, 32,  1>;
  template<std::signed_integral T> extern _::fixed_vint64m1_t         rvv_register<T, 64,  1>;
  template<std::signed_integral T> extern _::fixed_vint8m2_t          rvv_register<T,  8,  2>;
  template<std::signed_integral T> extern _::fixed_vint16m2_t         rvv_register<T, 16,  2>;
  template<std::signed_integral T> extern _::fixed_vint32m2_t         rvv_register<T, 32,  2>;
  template<std::signed_integral T> extern _::fixed_vint64m2_t         rvv_register<T, 64,  2>;
  template<std::signed_integral T> extern _::fixed_vint8m4_t          rvv_register<T,  8,  4>;
  template<std::signed_integral T> extern _::fixed_vint16m4_t         rvv_register<T, 16,  4>;
  template<std::signed_integral T> extern _::fixed_vint32m4_t         rvv_register<T, 32,  4>;
  template<std::signed_integral T> extern _::fixed_vint64m4_t         rvv_register<T, 64,  4>;
  template<std::signed_integral T> extern _::fixed_vint8m8_t          rvv_register<T,  8,  8>;
  template<std::signed_integral T> extern _::fixed_vint16m8_t         rvv_register<T, 16,  8>;
  template<std::signed_integral T> extern _::fixed_vint32m8_t         rvv_register<T, 32,  8>;
  template<std::signed_integral T> extern _::fixed_vint64m8_t         rvv_register<T, 64,  8>;
  template<std::signed_integral T> extern _::fixed_vint8mf2_t         rvv_register<T,  8, -2>;
  template<std::signed_integral T> extern _::fixed_vint16mf2_t        rvv_register<T, 16, -2>;
  template<std::signed_integral T> extern _::fixed_vint32mf2_t        rvv_register<T, 32, -2>;
  template<std::signed_integral T> extern _::fixed_vint8mf4_t         rvv_register<T,  8, -4>;
  template<std::signed_integral T> extern _::fixed_vint16mf4_t        rvv_register<T, 16, -4>;
  template<std::signed_integral T> extern _::fixed_vint8mf8_t         rvv_register<T,  8, -8>;

  template<std::unsigned_integral T> extern _::fixed_vuint8m1_t         rvv_register<T,  8,  1>;
  template<std::unsigned_integral T> extern _::fixed_vuint16m1_t        rvv_register<T, 16,  1>;
  template<std::unsigned_integral T> extern _::fixed_vuint32m1_t        rvv_register<T, 32,  1>;
  template<std::unsigned_integral T> extern _::fixed_vuint64m1_t        rvv_register<T, 64,  1>;
  template<std::unsigned_integral T> extern _::fixed_vuint8m2_t         rvv_register<T,  8,  2>;
  template<std::unsigned_integral T> extern _::fixed_vuint16m2_t        rvv_register<T, 16,  2>;
  template<std::unsigned_integral T> extern _::fixed_vuint32m2_t        rvv_register<T, 32,  2>;
  template<std::unsigned_integral T> extern _::fixed_vuint64m2_t        rvv_register<T, 64,  2>;
  template<std::unsigned_integral T> extern _::fixed_vuint8m4_t         rvv_register<T,  8,  4>;
  template<std::unsigned_integral T> extern _::fixed_vuint16m4_t        rvv_register<T, 16,  4>;
  template<std::unsigned_integral T> extern _::fixed_vuint32m4_t        rvv_register<T, 32,  4>;
  template<std::unsigned_integral T> extern _::fixed_vuint64m4_t        rvv_register<T, 64,  4>;
  template<std::unsigned_integral T> extern _::fixed_vuint8m8_t         rvv_register<T,  8,  8>;
  template<std::unsigned_integral T> extern _::fixed_vuint16m8_t        rvv_register<T, 16,  8>;
  template<std::unsigned_integral T> extern _::fixed_vuint32m8_t        rvv_register<T, 32,  8>;
  template<std::unsigned_integral T> extern _::fixed_vuint64m8_t        rvv_register<T, 64,  8>;
  template<std::unsigned_integral T> extern _::fixed_vuint8mf2_t        rvv_register<T,  8, -2>;
  template<std::unsigned_integral T> extern _::fixed_vuint16mf2_t       rvv_register<T, 16, -2>;
  template<std::unsigned_integral T> extern _::fixed_vuint32mf2_t       rvv_register<T, 32, -2>;
  template<std::unsigned_integral T> extern _::fixed_vuint8mf4_t        rvv_register<T,  8, -4>;
  template<std::unsigned_integral T> extern _::fixed_vuint16mf4_t       rvv_register<T, 16, -4>;
  template<std::unsigned_integral T> extern _::fixed_vuint8mf8_t        rvv_register<T,  8, -8>;

  // ---------------------------------------------------------------------------------------------
  // RVV logical register
  template<typename T, std::size_t Ratio>
  extern _::no_rvv_register<T, Ratio> rvv_logical_register;

  template<typename T> extern _::fixed_vbool1_t           rvv_logical_register<T,  1>;
  template<typename T> extern _::fixed_vbool2_t           rvv_logical_register<T,  2>;
  template<typename T> extern _::fixed_vbool4_t           rvv_logical_register<T,  4>;
  template<typename T> extern _::fixed_vbool8_t           rvv_logical_register<T,  8>;
  template<typename T> extern _::fixed_vbool16_t          rvv_logical_register<T, 16>;
  template<typename T> extern _::fixed_vbool32_t          rvv_logical_register<T, 32>;
  template<typename T> extern _::fixed_vbool64_t          rvv_logical_register<T, 64>;

  // ---------------------------------------------------------------------------------------------
  template<typename T, width_type N, rvv_abi ABI>
    requires((sizeof(T) * 8 * N) <= (__riscv_v_fixed_vlen * ABI::max_lmul))
  extern decltype(rvv_register<T, sizeof(T) * 8, _::rvv_lmul_v<T, N>>) as_register<T, N, ABI>;

  template<typename T, width_type N, rvv_abi ABI>
  extern decltype(rvv_logical_register<T, _::rvv_logical_ratio_v<T, N>>) as_logical_register<T, N, ABI>;
}