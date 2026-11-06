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
  template<std::size_t Width> struct arm_abi_
  {
    static constexpr std::size_t bits             = Width;
    static constexpr std::size_t bytes            = Width/8;
    static constexpr bool        is_wide_logical  = true;
    static constexpr bool        has_defined_logical_tail = true;
  };

  struct arm_64_  : arm_abi_< 64> {};
  struct arm_128_ : arm_abi_<128> {};

  //================================================================================================
  // Dispatching tag for ARM SIMD implementation
  //================================================================================================
  struct neon128_ : simd_api<simd_   , spy::neon_>  { using is_arm = void; };
  struct asimd_   : simd_api<neon128_, spy::asimd_> { using is_arm = void; };

  //================================================================================================
  // NEON extensions tag objects
  //================================================================================================
  inline constexpr neon128_ neon    = {};
  inline constexpr asimd_   asimd   = {};

  //================================================================================================
  // ARM ABI concept
  //================================================================================================
  template<typename T> concept arm_abi = _::one_of<T, arm_64_, arm_128_>;
  template<typename T> concept arm_tag = requires(T) { typename T::is_arm; };

  namespace _
  {
    template<typename T, eve::arm_abi ABI>
    inline constexpr bool use_complete_storage<T,ABI> = ((T::size() * sizeof(typename T::value_type)) >= 8);

    template<typename T, eve::arm_abi ABI>
    inline constexpr width_type expected_width<T, ABI> = ABI::bytes / sizeof(T);

    template<typename T, eve::arm_abi ABI>
    inline constexpr width_type fundamental_width<T,ABI> = 8 / sizeof(T);
  }
}
