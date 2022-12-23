//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
    static constexpr bool is_full = ((Type::size() * sizeof(typename Type::value_type)) >= Size/8);

    template<typename Type>
    static constexpr std::size_t fundamental_cardinal = bytes / sizeof(Type);

    template<typename Type>
    static constexpr std::size_t expected_cardinal = fundamental_cardinal<Type>;
  };

  struct arm_sve_128_ : sve_abi_<128> {};
  struct arm_sve_256_ : sve_abi_<256> {};
  struct arm_sve_512_ : sve_abi_<512> {};

  //================================================================================================
  // Dispatching tag for ARM SIMD implementation
  //================================================================================================
  struct sve_     : simd_api<simd_   , spy::sve_>       {  using is_sve = void;  };
  struct sve_vls_ : simd_api<sve_    , spy::fixed_sve_> {  using is_sve = void;  };
  struct sve128_  : simd_api<sve_vls_, spy::fixed_sve_> {  using is_sve = void;  };
  struct sve256_  : simd_api<sve_vls_, spy::fixed_sve_> {  using is_sve = void;  };
  struct sve512_  : simd_api<sve_vls_, spy::fixed_sve_> {  using is_sve = void;  };

  //================================================================================================
  // SVE extensions tag objects
  //================================================================================================
  inline constexpr sve_     sve       = {};
  inline constexpr sve_vls_ sve_vls   = {};
  inline constexpr sve128_  sve128    = {};
  inline constexpr sve256_  sve256    = {};
  inline constexpr sve512_  sve512    = {};

  //================================================================================================
  // ARM SVE ABI concept
  //================================================================================================
  template<typename T> concept sve_abi = detail::is_one_of<T> ( detail::types < arm_sve_128_
                                                                              , arm_sve_256_
                                                                              , arm_sve_512_
                                                                              > {}
                                                              );
  template<typename T> concept sve_tag = requires(T) { typename T::is_sve; };
}
