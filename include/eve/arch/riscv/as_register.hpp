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
#include <eve/traits/as_integer.hpp>

#include <type_traits>

namespace eve
{
  template<typename T>
  struct logical;
}

#if defined(EVE_RVV_M)
#  error EVE_RETURN_M already defined
#endif

#if defined(EVE_RVV_MF)
#  error EVE_RETURN_MF already defined
#endif

#define EVE_RVV_MF(REG, LMUL) (REG __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / LMUL)))){};
#define EVE_RVV_M(REG, LMUL) (REG __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * LMUL)))){};

namespace eve
{
  template<typename T, typename N, rvv_abi ABI>
  consteval auto find_register_type(as<T>, N, ABI)
  {
    constexpr auto lmul = detail::rvv_lmul_v<T, N>;
    constexpr size_t element_bit_size = sizeof(T) * 8;

    static_assert((element_bit_size * N::value) <= (__riscv_v_fixed_vlen * ABI::max_lmul),
      "[eve riscv] Type is not usable in SIMD register (too big)");

    if constexpr (std::floating_point<T>)
    {
      if constexpr (lmul == 1)
      {
        if      constexpr (element_bit_size == 32) return EVE_RVV_M(vfloat32m1_t, 1);
        else if constexpr (element_bit_size == 64) return EVE_RVV_M(vfloat64m1_t, 1);
      }
      else if constexpr (lmul == 2)
      {
        if      constexpr (element_bit_size == 32) return EVE_RVV_M(vfloat32m2_t, 2);
        else if constexpr (element_bit_size == 64) return EVE_RVV_M(vfloat64m2_t, 2);
      }
      else if constexpr (lmul == 4)
      {
        if      constexpr (element_bit_size == 32) return EVE_RVV_M(vfloat32m4_t, 4);
        else if constexpr (element_bit_size == 64) return EVE_RVV_M(vfloat64m4_t, 4);
      }
      else if constexpr (lmul == 8)
      {
        if      constexpr (element_bit_size == 32) return EVE_RVV_M(vfloat32m8_t, 8);
        else if constexpr (element_bit_size == 64) return EVE_RVV_M(vfloat64m8_t, 8);
      }
      else if constexpr (lmul == -2)
      {
        if      constexpr (element_bit_size == 32) return EVE_RVV_MF(vfloat32mf2_t, 2);
      }
      // MF8, MF4 for float not supported.
    }
    else if constexpr (std::signed_integral<T>)
    {
      if constexpr (lmul == 1)
      {
        if      constexpr (element_bit_size == 8 ) return EVE_RVV_M(vint8m1_t, 1);
        else if constexpr (element_bit_size == 16) return EVE_RVV_M(vint16m1_t, 1);
        else if constexpr (element_bit_size == 32) return EVE_RVV_M(vint32m1_t, 1);
        else if constexpr (element_bit_size == 64) return EVE_RVV_M(vint64m1_t, 1);
      }
      else if constexpr (lmul == 2)
      {
        if      constexpr (element_bit_size == 8 ) retunr EVE_RVV_M(vint8m2_t, 2);
        else if constexpr (element_bit_size == 16) return EVE_RVV_M(vint16m2_t, 2);
        else if constexpr (element_bit_size == 32) return EVE_RVV_M(vint32m2_t, 2);
        else if constexpr (element_bit_size == 64) return EVE_RVV_M(vint64m2_t, 2);
      }
      else if constexpr (lmul == 4)
      {
        if      constexpr (element_bit_size == 8 ) return EVE_RVV_M(vint8m4_t, 4);
        else if constexpr (element_bit_size == 16) return EVE_RVV_M(vint16m4_t, 4);
        else if constexpr (element_bit_size == 32) return EVE_RVV_M(vint32m4_t, 4);
        else if constexpr (element_bit_size == 64) return EVE_RVV_M(vint64m4_t, 4);
      }
      else if constexpr (lmul == 8)
      {
        if      constexpr (element_bit_size == 8 ) return EVE_RVV_M(vint8m8_t, 8);
        else if constexpr (element_bit_size == 16) return EVE_RVV_M(vint16m8_t, 8);
        else if constexpr (element_bit_size == 32) return EVE_RVV_M(vint32m8_t, 8);
        else if constexpr (element_bit_size == 64) return EVE_RVV_M(vint64m8_t, 8);
      }
      else if constexpr (lmul == -2)
      {
        if      constexpr (element_bit_size == 8 ) return EVE_RVV_MF(vint8mf2_t, 2);
        else if constexpr (element_bit_size == 16) return EVE_RVV_MF(vint16mf2_t, 2);
        else if constexpr (element_bit_size == 32) return EVE_RVV_MF(vint32mf2_t, 2);
      }
      else if constexpr (lmul == -4)
      {
        if      constexpr (element_bit_size == 8 ) return EVE_RVV_MF(vint8mf4_t, 4);
        else if constexpr (element_bit_size == 16) return EVE_RVV_MF(vint16mf4_t, 4);
      }
      else if constexpr (lmul == -8)
      {
        if      constexpr (element_bit_size == 8 ) return EVE_RVV_MF(vint8mf8_t, 8);
      }
    }
    else if constexpr (std::unsigned_integral<T>)
    {
      if constexpr (lmul == 1)
      {
        if      constexpr (element_bit_size == 8 ) return EVE_RVV_M(vuint8m1_t, 1);
        else if constexpr (element_bit_size == 16) return EVE_RVV_M(vuint16m1_t, 1);
        else if constexpr (element_bit_size == 32) return EVE_RVV_M(vuint32m1_t, 1);
        else if constexpr (element_bit_size == 64) return EVE_RVV_M(vuint64m1_t, 1);
      }
      else if constexpr (lmul == 2)
      {
        if      constexpr (element_bit_size == 8 ) return EVE_RVV_M(vuint8m2_t, 2);
        else if constexpr (element_bit_size == 16) return EVE_RVV_M(vuint16m2_t, 2);
        else if constexpr (element_bit_size == 32) return EVE_RVV_M(vuint32m2_t, 2);
        else if constexpr (element_bit_size == 64) return EVE_RVV_M(vuint64m2_t, 2);
      }
      else if constexpr (lmul == 4)
      {
        if      constexpr (element_bit_size == 8 ) return EVE_RVV_M(vuint8m4_t, 4);
        else if constexpr (element_bit_size == 16) return EVE_RVV_M(vuint16m4_t, 4);
        else if constexpr (element_bit_size == 32) return EVE_RVV_M(vuint32m4_t, 4);
        else if constexpr (element_bit_size == 64) return EVE_RVV_M(vuint64m4_t, 4);
      }
      else if constexpr (lmul == 8)
      {
        if      constexpr (element_bit_size == 8 ) return EVE_RVV_M(vuint8m8_t, 8);
        else if constexpr (element_bit_size == 16) return EVE_RVV_M(vuint16m8_t, 8);
        else if constexpr (element_bit_size == 32) return EVE_RVV_M(vuint32m8_t, 8);
        else if constexpr (element_bit_size == 64) return EVE_RVV_M(vuint64m8_t, 8);
      }
      else if constexpr (lmul == -2)
      {
        if      constexpr (element_bit_size == 8 ) return EVE_RVV_MF(vuint8mf2_t, 2);
        else if constexpr (element_bit_size == 16) return EVE_RVV_MF(vuint16mf2_t, 2);
        else if constexpr (element_bit_size == 32) return EVE_RVV_MF(vuint32mf2_t, 2);
      }
      else if constexpr (lmul == -4)
      {
        if      constexpr (element_bit_size == 8 ) return EVE_RVV_MF(vuint8mf4_t, 4);
        else if constexpr (element_bit_size == 16) return EVE_RVV_MF(vuint16mf4_t, 4);
      }
      else if constexpr (lmul == -8)
      {
        if      constexpr (element_bit_size == 8 ) return EVE_RVV_MF(vuint8mf8_t, 8);
      }
    }
  }

  // ---------------------------------------------------------------------------------------------
  // logical cases
  template<typename T, typename N>
  consteval auto find_logical_register_type(as<T>, N, rvv_abi auto)
  {
    constexpr size_t ratio = detail::rvv_logical_ratio_v<T, N>;

    if      constexpr (ratio == 1 ) return EVE_RVV_MF(vbool1_t, 1);
    else if constexpr (ratio == 2 ) return EVE_RVV_MF(vbool2_t, 2);
    else if constexpr (ratio == 4 ) return EVE_RVV_MF(vbool4_t, 4);
    else if constexpr (ratio == 8 ) return EVE_RVV_MF(vbool8_t, 8);
    else if constexpr (ratio == 16) return EVE_RVV_MF(vbool16_t, 16);
    else if constexpr (ratio == 32) return EVE_RVV_MF(vbool32_t, 32);
    else if constexpr (ratio == 64) return EVE_RVV_MF(vbool64_t, 64);
  }
}

#undef EVE_RVV_MF
#undef EVE_RVV_M
