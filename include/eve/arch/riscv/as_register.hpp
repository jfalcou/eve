//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/riscv/predef.hpp>
#include <eve/traits/as_integer.hpp>

#include <type_traits>
#if defined(EVE_HW_RISCV_SVE)
namespace eve
{
template<typename T> struct logical;
}

namespace eve
{
template<typename Type, typename Size, rvv_abi ABI> struct as_register<Type, Size, ABI>
{
  static constexpr auto lmul = riscv_rvv_dyn_::getLMUL<Type>(Size::value);

  static constexpr bool is_fp_v     = std::is_floating_point_v<Type>;
  static constexpr bool is_signed_v = std::is_signed_v<Type>;

#  ifdef EVE_RISCV_REG_CHOOSE
#    error EVE_RISCV_REG_CHOOSE defined
#  endif
#  define EVE_RISCV_REG_CHOOSE(name_part, bsize, lmul_name, lmul_expr)                             \
    if constexpr( bin_size == bsize )                                                              \
    {                                                                                              \
      using type = name_part##bsize##lmul_name##_t                                                 \
          __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * lmul_expr)));                \
      return type {};                                                                              \
    }

#  ifdef EVE_DEFINE_LMUL_FUNC
#    error EVE_DEFINE_LMUL_FUNC defined
#  endif
#  define EVE_DEFINE_LMUL_FUNC(name_part, lmul_name, lmul_expr)                                    \
    static consteval auto find_##name_part##lmul_name()                                            \
    {                                                                                              \
      constexpr size_t bin_size = sizeof(Type) * 8;                                                \
      EVE_RISCV_SIZE8(EVE_RISCV_REG_CHOOSE(name_part, 8, lmul_name, lmul_expr));                   \
      EVE_RISCV_SIZE16(EVE_RISCV_REG_CHOOSE(name_part, 16, lmul_name, lmul_expr));                 \
      EVE_RISCV_SIZE32(EVE_RISCV_REG_CHOOSE(name_part, 32, lmul_name, lmul_expr));                 \
      EVE_RISCV_SIZE64(EVE_RISCV_REG_CHOOSE(name_part, 64, lmul_name, lmul_expr));                 \
    }

#  define EVE_RISCV_SIZE8(X)  X
#  define EVE_RISCV_SIZE16(X) X
#  define EVE_RISCV_SIZE32(X) X
#  define EVE_RISCV_SIZE64(X) X

  EVE_DEFINE_LMUL_FUNC(vint, m1, 1)
  EVE_DEFINE_LMUL_FUNC(vint, m2, 2)
  EVE_DEFINE_LMUL_FUNC(vint, m4, 4)
  EVE_DEFINE_LMUL_FUNC(vint, m8, 8)
  EVE_DEFINE_LMUL_FUNC(vuint, m1, 1)
  EVE_DEFINE_LMUL_FUNC(vuint, m2, 2)
  EVE_DEFINE_LMUL_FUNC(vuint, m4, 4)
  EVE_DEFINE_LMUL_FUNC(vuint, m8, 8)
// for lmul 1/2  sew 64 not awailable
#  undef EVE_RISCV_SIZE64
#  define EVE_RISCV_SIZE64(X)
  EVE_DEFINE_LMUL_FUNC(vint, mf2, 1 / 2)
  EVE_DEFINE_LMUL_FUNC(vuint, mf2, 1 / 2)
// for lmul 1/4 sew 32 not awailable
#  undef EVE_RISCV_SIZE32
#  define EVE_RISCV_SIZE32(X)
  EVE_DEFINE_LMUL_FUNC(vint, mf4, 1 / 4)
  EVE_DEFINE_LMUL_FUNC(vuint, mf4, 1 / 4)
// for lmul 1/8 sew 16 not awailable
#  undef EVE_RISCV_SIZE16
#  define EVE_RISCV_SIZE16(X)
  EVE_DEFINE_LMUL_FUNC(vint, mf8, 1 / 8)
  EVE_DEFINE_LMUL_FUNC(vuint, mf8, 1 / 8)

  // for float we can have only size: 16(hf), 32(float), 64(double)

#  undef EVE_RISCV_SIZE8
#  undef EVE_RISCV_SIZE16
#  undef EVE_RISCV_SIZE32
#  undef EVE_RISCV_SIZE64
#  define EVE_RISCV_SIZE8(X)
#  define EVE_RISCV_SIZE16(X) X
#  define EVE_RISCV_SIZE32(X) X
#  define EVE_RISCV_SIZE64(X) X
  EVE_DEFINE_LMUL_FUNC(vfloat, m1, 1)
  EVE_DEFINE_LMUL_FUNC(vfloat, m2, 2)
  EVE_DEFINE_LMUL_FUNC(vfloat, m4, 4)
  EVE_DEFINE_LMUL_FUNC(vfloat, m8, 8)
// for lmul 1/2  sew 64 not awailable
#  undef EVE_RISCV_SIZE64
#  define EVE_RISCV_SIZE64(X)
  EVE_DEFINE_LMUL_FUNC(vfloat, mf2, 1 / 2)
#  undef EVE_RISCV_SIZE32
#  define EVE_RISCV_SIZE32(X)
  EVE_DEFINE_LMUL_FUNC(vfloat, mf4, 1 / 4)
  // lmul 1/8 for fp not awailable

#  undef EVE_RISCV_REG_CHOOSE
#  undef EVE_RISCV_SIZE8
#  undef EVE_RISCV_SIZE16
#  undef EVE_RISCV_SIZE32
#  undef EVE_RISCV_SIZE64

#  ifdef EVE_RISCV_LMUL_VARIANT
#    error EVE_RISCV_LMUL_VARIANT defined
#  endif
#  define EVE_RISCV_LMUL_VARIANT(name_part)                                                        \
    static consteval auto find_##name_part()                                                       \
    {                                                                                              \
      if constexpr( lmul == 1 ) return find_##name_part##m1();                                     \
      if constexpr( lmul == 2 ) return find_##name_part##m2();                                     \
      if constexpr( lmul == 4 ) return find_##name_part##m4();                                     \
      if constexpr( lmul == 8 ) return find_##name_part##m8();                                     \
      if constexpr( lmul == -2 ) return find_##name_part##mf2();                                   \
      if constexpr( lmul == -4 ) return find_##name_part##mf4();                                   \
      FRAC_LMUL_8(if constexpr( lmul == -8 ) return find_##name_part##mf8();)                      \
    }

#  define FRAC_LMUL_8(X) X
  EVE_RISCV_LMUL_VARIANT(vint)
  EVE_RISCV_LMUL_VARIANT(vuint)
#  undef FRAC_LMUL_8
#  define FRAC_LMUL_8(X)
  EVE_RISCV_LMUL_VARIANT(vfloat)
#  undef FRAC_LMUL_8
#  undef EVE_RISCV_LMUL_VARIANT

  public:
  static consteval auto find()
  {
    constexpr auto width = sizeof(Type) * Size::value * 8;

    static_assert(width <= __riscv_v_fixed_vlen * ABI::MaxLmul,
                  "[eve riscv] - Type is not usable in SIMD register (too big)");

    if constexpr( is_fp_v ) return find_vfloat();
    if constexpr( !is_fp_v && is_signed_v ) return find_vint();
    if constexpr( !is_fp_v && !is_signed_v ) return find_vuint();
  }
  using type = decltype(find());
  static_assert(!std::is_void_v<type>,
                "[eve riscv] - Type is not usable in a SIMD register (unknown type)");
};

// ---------------------------------------------------------------------------------------------
// logical cases
template<typename Type, typename Size, rvv_abi ABI> struct as_logical_register<Type, Size, ABI>
{
  static constexpr auto   lmul     = riscv_rvv_dyn_::getLMUL<Type>(Size::value);
  static constexpr size_t size     = sizeof(Type) * 8;
  static constexpr size_t bit_size = lmul > 0 ? size / lmul : size * (-lmul);

#  ifdef EVE_RVV_RET_MASK_TYPE
#    error EVE_RVV_RET_MASK_TYPE defined
#  endif
#  define EVE_RVV_RET_MASK_TYPE(bit_size)                                                          \
    using type = vbool##bit_size##_t                                                               \
        __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / bit_size)));                   \
    return type                                                                                    \
    {}

  static constexpr auto find()
  {
    if constexpr( bit_size == 1 ) { EVE_RVV_RET_MASK_TYPE(1); }
    if constexpr( bit_size == 2 ) { EVE_RVV_RET_MASK_TYPE(2); }
    if constexpr( bit_size == 4 ) { EVE_RVV_RET_MASK_TYPE(4); }
    if constexpr( bit_size == 8 ) { EVE_RVV_RET_MASK_TYPE(8); }
    if constexpr( bit_size == 16 ) { EVE_RVV_RET_MASK_TYPE(16); }
    if constexpr( bit_size == 32 ) { EVE_RVV_RET_MASK_TYPE(32); }
    if constexpr( bit_size == 64 ) { EVE_RVV_RET_MASK_TYPE(64); }
  }

#  undef EVE_RVV_RET_MASK_TYPE

  using type = decltype(find());
  static_assert(!std::is_void_v<type>,
                "[eve riscv] - Type is not usable as logical(mask) SIMD register");
};
}
#endif
