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
#include <eve/detail/meta.hpp>

#include <optional>

namespace eve
{
//================================================================================================
// ABI tags for all RISCV bits SIMD registers
//================================================================================================
template<std::size_t vector_register_bit_size> struct rvv_abi_
{
  static constexpr std::size_t max_lmul        = 8;
  static constexpr std::size_t bits            = vector_register_bit_size * max_lmul;
  static constexpr std::size_t bytes           = bits / 8;
  static constexpr bool        is_wide_logical = false;

  template<typename Type>
  static constexpr std::size_t fundamental_vector_size =
      vector_register_bit_size * sizeof(Type) / 8;

  template<typename Type>
  static constexpr std::size_t fundamental_cardinal =
      fundamental_vector_size<Type> / sizeof(Type) / 8;
  // Work in terms of vector intrinsics types
  template<typename Type>
  static constexpr bool is_full = ((Type::size() * sizeof(typename Type::value_type))
                                   >= fundamental_vector_size<typename Type::value_type> / 8);

  template<typename Type>
  static constexpr std::size_t expected_cardinal =
      vector_register_bit_size / 8 / sizeof(Type) * max_lmul;
};

#ifdef __riscv_v_fixed_vlen
struct riscv_ : rvv_abi_<__riscv_v_fixed_vlen>
{};
#else
// Needed for comparison purposes in core EVE.
// No RISC-V specific code should be generated in this case.
struct riscv_ : rvv_abi_<1>
{};
#endif

//================================================================================================
// Dispatching tag for RISC-V SIMD implementation
//================================================================================================
struct rvv_ : simd_api<simd_, spy::fixed_rvv_>
{
  using is_rvv = void;
};

//================================================================================================
// RISC-V extensions tag objects
//================================================================================================
inline constexpr rvv_ rvv = {};

//================================================================================================
// RISC-V RVV ABI concept
//================================================================================================
template<typename T>
concept rvv_abi = detail::is_one_of<T>(detail::types<riscv_> {});
template<typename T>
concept rvv_tag = requires(T) { typename T::is_rvv; };
}
