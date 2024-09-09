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
#if defined(EVE_INCLUDE_RISCV_HEADER)

namespace eve
{
template<typename T> struct logical;
}

#  if defined(EVE_RETURN_M)
#    error EVE_RETURN_M already defined
#  endif

#  if defined(EVE_RETURN_MF)
#    error EVE_RETURN_MF already defined
#  endif

#  define EVE_RETURN_MF(REG, LMUL)                                                                 \
    using type = REG __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / LMUL)));          \
    return type                                                                                    \
    {}

#  define EVE_RETURN_M(REG, LMUL)                                                                  \
    using type = REG __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * LMUL)));          \
    return type                                                                                    \
    {}

namespace eve
{
template<typename Type, typename Size, rvv_abi ABI> struct as_register<Type, Size, ABI>
{
  static constexpr auto lmul = detail::rvv_lmul_v<Type, Size>;

  static consteval auto find_vint_mf8()
  {
    constexpr std::size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 8 ) { EVE_RETURN_MF(vint8mf8_t, 8); }
  }

  static consteval auto find_vint_mf4()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 8 ) { EVE_RETURN_MF(vint8mf4_t, 4); }
    else if constexpr( element_bit_size == 16 ) { EVE_RETURN_MF(vint16mf4_t, 4); }
  }

  static consteval auto find_vint_mf2()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 8 ) { EVE_RETURN_MF(vint8mf2_t, 2); }
    else if constexpr( element_bit_size == 16 ) { EVE_RETURN_MF(vint16mf2_t, 2); }
    else if constexpr( element_bit_size == 32 ) { EVE_RETURN_MF(vint32mf2_t, 2); }
  }

  static consteval auto find_vint_m1()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 8 ) { EVE_RETURN_M(vint8m1_t, 1); }
    else if constexpr( element_bit_size == 16 ) { EVE_RETURN_M(vint16m1_t, 1); }
    else if constexpr( element_bit_size == 32 ) { EVE_RETURN_M(vint32m1_t, 1); }
    else if constexpr( element_bit_size == 64 ) { EVE_RETURN_M(vint64m1_t, 1); }
  }

  static consteval auto find_vint_m2()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 8 ) { EVE_RETURN_M(vint8m2_t, 2); }
    else if constexpr( element_bit_size == 16 ) { EVE_RETURN_M(vint16m2_t, 2); }
    else if constexpr( element_bit_size == 32 ) { EVE_RETURN_M(vint32m2_t, 2); }
    else if constexpr( element_bit_size == 64 ) { EVE_RETURN_M(vint64m2_t, 2); }
  }

  static consteval auto find_vint_m4()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 8 ) { EVE_RETURN_M(vint8m4_t, 4); }
    else if constexpr( element_bit_size == 16 ) { EVE_RETURN_M(vint16m4_t, 4); }
    else if constexpr( element_bit_size == 32 ) { EVE_RETURN_M(vint32m4_t, 4); }
    else if constexpr( element_bit_size == 64 ) { EVE_RETURN_M(vint64m4_t, 4); }
  }

  static consteval auto find_vint_m8()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 8 ) { EVE_RETURN_M(vint8m8_t, 8); }
    else if constexpr( element_bit_size == 16 ) { EVE_RETURN_M(vint16m8_t, 8); }
    else if constexpr( element_bit_size == 32 ) { EVE_RETURN_M(vint32m8_t, 8); }
    else if constexpr( element_bit_size == 64 ) { EVE_RETURN_M(vint64m8_t, 8); }
  }

  static consteval auto find_vint()
  {
    if constexpr( lmul == 1 ) return find_vint_m1();
    else if constexpr( lmul == 2 ) return find_vint_m2();
    else if constexpr( lmul == 4 ) return find_vint_m4();
    else if constexpr( lmul == 8 ) return find_vint_m8();
    else if constexpr( lmul == -2 ) return find_vint_mf2();
    else if constexpr( lmul == -4 ) return find_vint_mf4();
    else if constexpr( lmul == -8 ) return find_vint_mf8();
  }

  static consteval auto find_vuint_mf8()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 8 ) { EVE_RETURN_MF(vuint8mf8_t, 8); }
  }

  static consteval auto find_vuint_mf4()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 8 ) { EVE_RETURN_MF(vuint8mf4_t, 4); }
    else if constexpr( element_bit_size == 16 ) { EVE_RETURN_MF(vuint16mf4_t, 4); }
  }

  static consteval auto find_vuint_mf2()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 8 ) { EVE_RETURN_MF(vuint8mf2_t, 2); }
    else if constexpr( element_bit_size == 16 ) { EVE_RETURN_MF(vuint16mf2_t, 2); }
    else if constexpr( element_bit_size == 32 ) { EVE_RETURN_MF(vuint32mf2_t, 2); }
  }

  static consteval auto find_vuint_m1()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 8 ) { EVE_RETURN_M(vuint8m1_t, 1); }
    else if constexpr( element_bit_size == 16 ) { EVE_RETURN_M(vuint16m1_t, 1); }
    else if constexpr( element_bit_size == 32 ) { EVE_RETURN_M(vuint32m1_t, 1); }
    else if constexpr( element_bit_size == 64 ) { EVE_RETURN_M(vuint64m1_t, 1); }
  }

  static consteval auto find_vuint_m2()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 8 ) { EVE_RETURN_M(vuint8m2_t, 2); }
    else if constexpr( element_bit_size == 16 ) { EVE_RETURN_M(vuint16m2_t, 2); }
    else if constexpr( element_bit_size == 32 ) { EVE_RETURN_M(vuint32m2_t, 2); }
    else if constexpr( element_bit_size == 64 ) { EVE_RETURN_M(vuint64m2_t, 2); }
  }

  static consteval auto find_vuint_m4()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 8 ) { EVE_RETURN_M(vuint8m4_t, 4); }
    else if constexpr( element_bit_size == 16 ) { EVE_RETURN_M(vuint16m4_t, 4); }
    else if constexpr( element_bit_size == 32 ) { EVE_RETURN_M(vuint32m4_t, 4); }
    else if constexpr( element_bit_size == 64 ) { EVE_RETURN_M(vuint64m4_t, 4); }
  }

  static consteval auto find_vuint_m8()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 8 ) { EVE_RETURN_M(vuint8m8_t, 8); }
    else if constexpr( element_bit_size == 16 ) { EVE_RETURN_M(vuint16m8_t, 8); }
    else if constexpr( element_bit_size == 32 ) { EVE_RETURN_M(vuint32m8_t, 8); }
    else if constexpr( element_bit_size == 64 ) { EVE_RETURN_M(vuint64m8_t, 8); }
  }

  static consteval auto find_vuint()
  {
    if constexpr( lmul == 1 ) return find_vuint_m1();
    else if constexpr( lmul == 2 ) return find_vuint_m2();
    else if constexpr( lmul == 4 ) return find_vuint_m4();
    else if constexpr( lmul == 8 ) return find_vuint_m8();
    else if constexpr( lmul == -2 ) return find_vuint_mf2();
    else if constexpr( lmul == -4 ) return find_vuint_mf4();
    else if constexpr( lmul == -8 ) return find_vuint_mf8();
  }

  static consteval auto find_vfloat_mf2()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 32 ) { EVE_RETURN_MF(vfloat32mf2_t, 2); }
  }

  static consteval auto find_vfloat_m1()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 32 ) { EVE_RETURN_M(vfloat32m1_t, 1); }
    else if constexpr( element_bit_size == 64 ) { EVE_RETURN_M(vfloat64m1_t, 1); }
  }

  static consteval auto find_vfloat_m2()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 32 ) { EVE_RETURN_M(vfloat32m2_t, 2); }
    else if constexpr( element_bit_size == 64 ) { EVE_RETURN_M(vfloat64m2_t, 2); }
  }

  static consteval auto find_vfloat_m4()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 32 ) { EVE_RETURN_M(vfloat32m4_t, 4); }
    else if constexpr( element_bit_size == 64 ) { EVE_RETURN_M(vfloat64m4_t, 4); }
  }

  static consteval auto find_vfloat_m8()
  {
    constexpr size_t element_bit_size = sizeof(Type) * 8;
    if constexpr( element_bit_size == 32 ) { EVE_RETURN_M(vfloat32m8_t, 8); }
    else if constexpr( element_bit_size == 64 ) { EVE_RETURN_M(vfloat64m8_t, 8); }
  }

  static consteval auto find_vfloat()
  {
    if constexpr( lmul == 1 ) return find_vfloat_m1();
    else if constexpr( lmul == 2 ) return find_vfloat_m2();
    else if constexpr( lmul == 4 ) return find_vfloat_m4();
    else if constexpr( lmul == 8 ) return find_vfloat_m8();
    else if constexpr( lmul == -2 ) return find_vfloat_mf2();
    // MF8, MF4 for float not supported.
  }

  public:
  static consteval auto find()
  {
    constexpr auto width = sizeof(Type) * Size::value * 8;

    static_assert(width <= __riscv_v_fixed_vlen * ABI::max_lmul,
                  "[eve riscv] - sanity check. Type is not usable in SIMD register (too big)");
    if constexpr( std::is_floating_point_v<Type> ) return find_vfloat();
    else if constexpr( std::is_integral_v<Type> && std::is_signed_v<Type> ) return find_vint();
    else if constexpr( std::is_integral_v<Type> && std::is_unsigned_v<Type> ) return find_vuint();
  }
  using type = decltype(find());
  static_assert(!std::is_void_v<type>,
                "[eve riscv] - sanity check. Type is not usable in a SIMD register (unknown type)");
};

#  undef EVE_RETURN_MF
#  undef EVE_RETURN_M

// ---------------------------------------------------------------------------------------------
// logical cases
template<typename Type, typename Size, rvv_abi ABI> struct as_logical_register<Type, Size, ABI>
{
  static constexpr size_t ratio = detail::rvv_logical_ratio_v<Type, Size>;

  static constexpr auto find()
  {
    if constexpr( ratio == 1 )
    {
      using type = vbool1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen)));
      return type {};
    }
    else if constexpr( ratio == 2 )
    {
      using type = vbool2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
      return type {};
    }
    else if constexpr( ratio == 4 )
    {
      using type = vbool4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 4)));
      return type {};
    }
    else if constexpr( ratio == 8 )
    {
      using type = vbool8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 8)));
      return type {};
    }
    else if constexpr( ratio == 16 )
    {
      using type = vbool16_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 16)));
      return type {};
    }
    else if constexpr( ratio == 32 )
    {
      using type = vbool32_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 32)));
      return type {};
    }
    else if constexpr( ratio == 64 )
    {
      using type = vbool64_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 64)));
      return type {};
    }
  }

  using type = decltype(find());
  static_assert(!std::is_void_v<type>,
                "[eve riscv] - sanity check. Type is not usable as logical(mask) SIMD register");
};
}
#endif
