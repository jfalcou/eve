//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/cpu/tags.hpp>
#include <eve/arch/riscv/predef.hpp>
#include <eve/detail/meta.hpp>

namespace eve
{
  //================================================================================================
  // ABI tags for all RISCV bits SIMD registers
  //================================================================================================
  template<std::size_t Width> struct rvv_abi_
  {
    static constexpr std::size_t max_lmul        = 8;
    static constexpr std::size_t bits            = Width * max_lmul;
    static constexpr std::size_t bytes           = bits / 8;
    static constexpr bool        is_wide_logical = false;
    // RVV leaves the tail of a mask destination agnostic whatever vta says.
    static constexpr bool        has_defined_logical_tail = false;  
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
  struct rvv_ : simd_api<simd_, spy::fixed_rvv_> { using is_rvv = void; };
  
  //================================================================================================
  // RISC-V extensions tag objects
  //================================================================================================
  inline constexpr rvv_ rvv = {};
  
  //================================================================================================
  // RISC-V RVV ABI concept
  //================================================================================================
  template<typename T> concept rvv_abi = _::one_of<T, riscv_>;
  template<typename T> concept rvv_tag = requires(T) { typename T::is_rvv; };

  namespace _
  {
    template<typename T>
    inline constexpr width_type rvv_vector_size = (ABI::bits / ABI::max_lmul) * sizeof(T) / 8;
  
    // Work in terms of vector intrinsics types
    template<typename T, rvv_abi ABI>
    inline constexpr bool use_complete_storage<T,ABI> = ((T::size() * sizeof(typename T::value_type))
                                     >= rvv_vector_size<typename T::value_type> / 8);
    
    template<typename T, rvv_abi ABI>
    inline constexpr width_type fundamental_width<T,ABI> = rvv_vector_size<T> / sizeof(T) / 8;
  
    template<typename T, rvv_abi ABI>
    inline constexpr width_type expected_width<T,ABI> = (ABI::bits / ABI::max_lmul) / 8 / sizeof(T) * max_lmul;
  }
}
