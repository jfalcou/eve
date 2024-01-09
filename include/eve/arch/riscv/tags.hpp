//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/cardinals.hpp>
#include <eve/arch/cpu/tags.hpp>
#include <eve/arch/riscv/predef.hpp>
#include <eve/concept/scalar.hpp>
#include <eve/detail/meta.hpp>

#include <bit>

namespace eve
{
//================================================================================================
// ABI tags for all RISCV bits SIMD registers
//================================================================================================
template<std::size_t Size> struct rvv_abi_
{
  static constexpr std::size_t MaxLmul         = 8;
  static constexpr std::size_t bits            = Size * MaxLmul;
  static constexpr std::size_t bytes           = bits / 8;
  static constexpr bool        is_wide_logical = false;

  template<typename Type>
  static constexpr bool is_full = ((Type::size() * sizeof(typename Type::value_type)) >= bytes);

  template<typename Type>
  static constexpr std::size_t fundamental_cardinal = Size / 8 / sizeof(Type);

  template<typename Type>
  static constexpr std::size_t expected_cardinal = Size / 8 / sizeof(Type) * MaxLmul;

  template<typename Type> static consteval int get_min_frac_lmul()
  {
    auto type_size = sizeof(Type);
    if( type_size == 1 ) return 8;
    if( type_size == 2 ) return 4;
    if( type_size == 4 ) return 2;
    // for bigger types we can not use frac lmul.
    // Return bigger than size of vector register value.
    return Size + 1;
  }

  template<typename Type> static consteval int get_max_frac_lmul()
  {
    auto type_size = sizeof(Type);
    if( type_size <= 4 ) return 2;
    // for bigger types we can not use frac lmul.
    // Return bigger than size of vector register value.
    return Size + 1;
  }

  // return natural lmul if > 0, frac otherwise
  template<typename Type> static consteval int getLMUL(size_t cardinal)
  {
    auto binary_size   = cardinal * sizeof(Type) * 8;
    auto min_frac_lmul = get_min_frac_lmul<Type>();
    auto max_frac_lmul = get_max_frac_lmul<Type>();

    auto frac_lmul_border = Size / max_frac_lmul;
    if( binary_size <= frac_lmul_border )
    {
      auto frac_lmul = Size / binary_size;
      frac_lmul      = std::bit_floor(frac_lmul);
      if( frac_lmul > min_frac_lmul ) frac_lmul = min_frac_lmul;
      return -frac_lmul;
    }
    auto lmul = binary_size / Size;
    if( binary_size % Size ) ++lmul;
    return std::bit_ceil(lmul);
  }

  template<arithmetic_scalar_value T> using m1_fixed = fixed<Size / 8 / sizeof(T)>;
};

#ifdef __riscv_v_fixed_vlen
struct riscv_rvv_dyn_ : rvv_abi_<__riscv_v_fixed_vlen>
{};
#else
struct riscv_rvv_dyn_ : rvv_abi_<1>
{};
#endif

//================================================================================================
// Dispatching tag for RISC-V SIMD implementation
//================================================================================================
struct rvv_ : simd_api<simd_, spy::rvv_>
{
  using is_rvv = void;
};
struct rvv_api_ : simd_api<rvv_, spy::rvv_>
{
  using is_rvv = void;
};

//================================================================================================
// RISC-V extensions tag objects
//================================================================================================
inline constexpr rvv_     rvv     = {};
inline constexpr rvv_api_ rvv_api = {};

//================================================================================================
// RISC-V RVV ABI concept
//================================================================================================
template<typename T>
concept rvv_abi = detail::is_one_of<T>(detail::types<riscv_rvv_dyn_> {});
template<typename T>
concept rvv_tag = requires(T) { typename T::is_rvv; };
}
