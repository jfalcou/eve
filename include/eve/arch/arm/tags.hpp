//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/predef.hpp>
#include <eve/arch/cpu/tags.hpp>
#include <eve/detail/meta.hpp>

namespace eve
{
  // clang-format off
  //================================================================================================
  // ABI tags for all ARM bits SIMD registers
  //================================================================================================
  template<std::size_t Size, bool Logical> struct arm_abi_
  {
    static constexpr std::size_t bits                     = Size;
    static constexpr std::size_t bytes                    = Size/8;
    static constexpr bool        is_wide_logical = Logical;

    template<typename Type>
    static constexpr bool is_full = ((Type::size() * sizeof(typename Type::value_type)) >= 8);

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);

    template<typename Type>
    static constexpr std::size_t fundamental_cardinal = 8 / sizeof(Type);
  };

  struct arm_64_      : arm_abi_< 64,true>  {};
  struct arm_128_     : arm_abi_<128,true>  {};
  struct arm_sve_128_ : arm_abi_<128,false> {};
  struct arm_sve_256_ : arm_abi_<256,false> {};
  struct arm_sve_512_ : arm_abi_<512,false> {};

  //================================================================================================
  // Dispatching tag for ARM SIMD implementation
  //================================================================================================
  struct neon128_ : simd_api<simd_   , spy::neon_>      {};
  struct asimd_   : simd_api<neon128_, spy::asimd_>     {};
  struct sve128_  : simd_api<simd_   , spy::fixed_sve_> {};
  struct sve256_  : simd_api<simd_   , spy::fixed_sve_> {};
  struct sve512_  : simd_api<simd_   , spy::fixed_sve_> {};

  //================================================================================================
  // NEON extension tag objects
  //================================================================================================
  inline constexpr neon128_ neon    = {};
  inline constexpr asimd_   asimd   = {};
  inline constexpr sve128_  sve128  = {};
  inline constexpr sve256_  sve256  = {};
  inline constexpr sve512_  sve512  = {};

  //================================================================================================
  // ARM ABI concept
  //================================================================================================
  template<typename T> concept arm_abi = detail::is_one_of<T> ( detail::types<arm_64_,arm_128_> {});
  template<typename T> concept sve_abi = detail::is_one_of<T> ( detail::types < arm_sve_128_
                                                                              , arm_sve_256_
                                                                              , arm_sve_512_
                                                                              > {}
                                                              );
}
