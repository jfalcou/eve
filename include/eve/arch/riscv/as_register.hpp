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

  static consteval auto find_vint_mf8()
  {
    constexpr std::size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 8 )
    {
      using type = vint8mf8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 8)));
      return type {};
    }
  }

  static consteval auto find_vint_mf4()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 8 )
    {
      using type = vint8mf4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 4)));
      return type {};
    } else if constexpr( bin_size == 16 )
    {
      using type = vint16mf4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 4)));
      return type {};
    }
  }

  static consteval auto find_vint_mf2()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 8 )
    {
      using type = vint8mf2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
      return type {};
    } else if constexpr( bin_size == 16 )
    {
      using type = vint16mf2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
      return type {};
    } else if constexpr( bin_size == 32 )
    {
      using type = vint32mf2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
      return type {};
    }
  }

  static consteval auto find_vint_m1()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 8 )
    {
      using type = vint8m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen)));
      return type {};
    } else if constexpr( bin_size == 16 )
    {
      using type = vint16m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen)));
      return type {};
    } else if constexpr( bin_size == 32 )
    {
      using type = vint32m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen)));
      return type {};
    } else if constexpr( bin_size == 64 )
    {
      using type = vint64m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen)));
      return type {};
    }
  }

  static consteval auto find_vint_m2()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 8 )
    {
      using type = vint8m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
      return type {};
    } else if constexpr( bin_size == 16 )
    {
      using type = vint16m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
      return type {};
    } else if constexpr( bin_size == 32 )
    {
      using type = vint32m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
      return type {};
    } else if constexpr( bin_size == 64 )
    {
      using type = vint64m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
      return type {};
    }
  }

  static consteval auto find_vint_m4()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 8 )
    {
      using type = vint8m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
      return type {};
    } else if constexpr( bin_size == 16 )
    {
      using type = vint16m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
      return type {};
    } else if constexpr( bin_size == 32 )
    {
      using type = vint32m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
      return type {};
    } else if constexpr( bin_size == 64 )
    {
      using type = vint64m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
      return type {};
    }
  }

  static consteval auto find_vint_m8()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 8 )
    {
      using type = vint8m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
      return type {};
    } else if constexpr( bin_size == 16 )
    {
      using type = vint16m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
      return type {};
    } else if constexpr( bin_size == 32 )
    {
      using type = vint32m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
      return type {};
    } else if constexpr( bin_size == 64 )
    {
      using type = vint64m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
      return type {};
    }
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
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 8 )
    {
      using type = vuint8mf8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 8)));
      return type {};
    }
  }

  static consteval auto find_vuint_mf4()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 8 )
    {
      using type = vuint8mf4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 4)));
      return type {};
    } else if constexpr( bin_size == 16 )
    {
      using type = vuint16mf4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 4)));
      return type {};
    }
  }

  static consteval auto find_vuint_mf2()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 8 )
    {
      using type = vuint8mf2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
      return type {};
    } else if constexpr( bin_size == 16 )
    {
      using type = vuint16mf2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
      return type {};
    } else if constexpr( bin_size == 32 )
    {
      using type = vuint32mf2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
      return type {};
    }
  }

  static consteval auto find_vuint_m1()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 8 )
    {
      using type = vuint8m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen)));
      return type {};
    } else if constexpr( bin_size == 16 )
    {
      using type = vuint16m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen)));
      return type {};
    } else if constexpr( bin_size == 32 )
    {
      using type = vuint32m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen)));
      return type {};
    } else if constexpr( bin_size == 64 )
    {
      using type = vuint64m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen)));
      return type {};
    }
  }

  static consteval auto find_vuint_m2()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 8 )
    {
      using type = vuint8m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
      return type {};
    } else if constexpr( bin_size == 16 )
    {
      using type = vuint16m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
      return type {};
    } else if constexpr( bin_size == 32 )
    {
      using type = vuint32m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
      return type {};
    } else if constexpr( bin_size == 64 )
    {
      using type = vuint64m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
      return type {};
    }
  }

  static consteval auto find_vuint_m4()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 8 )
    {
      using type = vuint8m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
      return type {};
    } else if constexpr( bin_size == 16 )
    {
      using type = vuint16m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
      return type {};
    } else if constexpr( bin_size == 32 )
    {
      using type = vuint32m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
      return type {};
    } else if constexpr( bin_size == 64 )
    {
      using type = vuint64m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
      return type {};
    }
  }

  static consteval auto find_vuint_m8()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 8 )
    {
      using type = vuint8m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
      return type {};
    } else if constexpr( bin_size == 16 )
    {
      using type = vuint16m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
      return type {};
    } else if constexpr( bin_size == 32 )
    {
      using type = vuint32m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
      return type {};
    } else if constexpr( bin_size == 64 )
    {
      using type = vuint64m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
      return type {};
    }
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

  static consteval auto find_vfloat_mf4()
  {
    // For MF4 we have float16 types, but for now we do not support this, as
    // it requires additional RISC-V extension Zvfh.
    return;
  }

  static consteval auto find_vfloat_mf2()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 32 )
    {
      using type = vfloat32mf2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
      return type {};
    }
  }

  static consteval auto find_vfloat_m1()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 32 )
    {
      using type = vfloat32m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen)));
      return type {};
    } else if constexpr( bin_size == 64 )
    {
      using type = vfloat64m1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen)));
      return type {};
    }
  }

  static consteval auto find_vfloat_m2()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 32 )
    {
      using type = vfloat32m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
      return type {};
    } else if constexpr( bin_size == 64 )
    {
      using type = vfloat64m2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 2)));
      return type {};
    }
  }

  static consteval auto find_vfloat_m4()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 32 )
    {
      using type = vfloat32m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
      return type {};
    } else if constexpr( bin_size == 64 )
    {
      using type = vfloat64m4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 4)));
      return type {};
    }
  }

  static consteval auto find_vfloat_m8()
  {
    constexpr size_t bin_size = sizeof(Type) * 8;
    if constexpr( bin_size == 32 )
    {
      using type = vfloat32m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
      return type {};
    } else if constexpr( bin_size == 64 )
    {
      using type = vfloat64m8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen * 8)));
      return type {};
    }
  }

  static consteval auto find_vfloat()
  {
    if constexpr( lmul == 1 ) return find_vfloat_m1();
    else if constexpr( lmul == 2 ) return find_vfloat_m2();
    else if constexpr( lmul == 4 ) return find_vfloat_m4();
    else if constexpr( lmul == 8 ) return find_vfloat_m8();
    else if constexpr( lmul == -2 ) return find_vfloat_mf2();
    else if constexpr( lmul == -4 ) return find_vfloat_mf4();
    // MF8 for float not supported.
  }

  public:
  static consteval auto find()
  {
    constexpr auto width = sizeof(Type) * Size::value * 8;

    static_assert(width <= __riscv_v_fixed_vlen * ABI::MaxLmul,
                  "[eve riscv] - Type is not usable in SIMD register (too big)");
    if constexpr( is_fp_v ) return find_vfloat();
    else if constexpr( !is_fp_v && is_signed_v ) return find_vint();
    else if constexpr( !is_fp_v && !is_signed_v ) return find_vuint();
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

  static constexpr auto find()
  {
    if constexpr( bit_size == 1 )
    {
      using type = vbool1_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen)));
      return type {};
    } else if constexpr( bit_size == 2 )
    {
      using type = vbool2_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 2)));
      return type {};
    } else if constexpr( bit_size == 4 )
    {
      using type = vbool4_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 4)));
      return type {};
    } else if constexpr( bit_size == 8 )
    {
      using type = vbool8_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 8)));
      return type {};
    } else if constexpr( bit_size == 16 )
    {
      using type = vbool16_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 16)));
      return type {};
    } else if constexpr( bit_size == 32 )
    {
      using type = vbool32_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 32)));
      return type {};
    } else if constexpr( bit_size == 64 )
    {
      using type = vbool64_t __attribute__((riscv_rvv_vector_bits(__riscv_v_fixed_vlen / 64)));
      return type {};
    }
  }

  using type = decltype(find());
  static_assert(!std::is_void_v<type>,
                "[eve riscv] - Type is not usable as logical(mask) SIMD register");
};
}
#endif
