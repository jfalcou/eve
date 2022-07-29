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
  //================================================================================================
  // ABI tags for all ARM bits SIMD registers
  //================================================================================================
  template<std::size_t Size> struct sve_abi_
  {
    static constexpr std::size_t bits             = Size;
    static constexpr std::size_t bytes            = Size/8;
    static constexpr bool        is_wide_logical  = false;

    template<typename Type>
    static constexpr bool is_full = ((Type::size() * sizeof(typename Type::value_type)) >= 8);

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);

    template<typename Type>
    static constexpr std::size_t fundamental_cardinal = 8 / sizeof(Type);
  };

  struct arm_sve_128_ : sve_abi_<128> {};
  struct arm_sve_256_ : sve_abi_<256> {};
  struct arm_sve_512_ : sve_abi_<512> {};

  //================================================================================================
  // Dispatching tag for ARM SIMD implementation
  //================================================================================================
  struct sve_fixed_ : simd_api<simd_      , spy::fixed_sve_> {};
  struct sve128_  : simd_api<sve_fixed_   , spy::fixed_sve_> {};
  struct sve256_  : simd_api<sve_fixed_   , spy::fixed_sve_> {};
  struct sve512_  : simd_api<sve_fixed_   , spy::fixed_sve_> {};

  //================================================================================================
  // SVE extensions tag objects
  //================================================================================================
  inline constexpr sve128_  sve128  = {};
  inline constexpr sve256_  sve256  = {};
  inline constexpr sve512_  sve512  = {};

  //================================================================================================
  // ARM SVE ABI concept
  //================================================================================================
  template<typename T> concept sve_abi = detail::is_one_of<T> ( detail::types < arm_sve_128_
                                                                              , arm_sve_256_
                                                                              , arm_sve_512_
                                                                              > {}
                                                              );
}
