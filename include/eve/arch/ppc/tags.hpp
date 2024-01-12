//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include "eve/detail/spy.hpp"
#include <eve/arch/cpu/tags.hpp>
#include <eve/arch/ppc/predef.hpp>
#include <eve/detail/meta.hpp>

namespace eve
{
  // clang-format off
  //================================================================================================
  // Tag for all PPC SIMD ABI
  //================================================================================================
  struct ppc_
  {
    static constexpr std::size_t bits                     = 128;
    static constexpr std::size_t bytes                    = 16;
    static constexpr bool        is_wide_logical = true;

    template<typename Type>
    static constexpr bool is_full = ((Type::size() * sizeof(typename Type::value_type)) >= 16);

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);

    template<typename Type>
    static constexpr std::size_t fundamental_cardinal = 16 / sizeof(Type);
  };

  //================================================================================================
  // Dispatching tag for V*X SIMD implementation
  //================================================================================================
  struct  vmx_      : simd_api<simd_    , spy::vmx_     > { using is_ppc = void; };
  struct  vmx_2_03_ : simd_api<vmx_     , spy::vmx_2_03_> { using is_ppc = void; };
  struct  vmx_2_05_ : simd_api<vmx_2_03_, spy::vmx_2_05_> { using is_ppc = void; };
  struct  vmx_2_06_ : simd_api<vmx_2_05_, spy::vmx_2_06_> { using is_ppc = void; };
  struct  vmx_2_07_ : simd_api<vmx_2_06_, spy::vmx_2_07_> { using is_ppc = void; };
  struct  vmx_3_00_ : simd_api<vmx_2_07_, spy::vmx_3_00_> { using is_ppc = void; };
  struct  vmx_3_01_ : simd_api<vmx_3_00_, spy::vmx_3_01_> { using is_ppc = void; };
  struct  vsx_      : simd_api<vmx_3_01_, spy::vsx_     > { using is_ppc = void; };
  struct  vsx_2_06_ : simd_api<vsx_     , spy::vsx_2_06_> { using is_ppc = void; };
  struct  vsx_2_07_ : simd_api<vsx_2_06_, spy::vsx_2_07_> { using is_ppc = void; };
  struct  vsx_3_00_ : simd_api<vsx_2_07_, spy::vsx_3_00_> { using is_ppc = void; };
  struct  vsx_3_01_ : simd_api<vsx_3_00_, spy::vsx_3_01_> { using is_ppc = void; };

//================================================================================================
  //  V*X extension tag objects
  //================================================================================================
  inline constexpr vmx_       vmx       = {};
  inline constexpr vmx_2_03_  vmx_2_03  = {};
  inline constexpr vmx_2_05_  vmx_2_05  = {};
  inline constexpr vmx_2_06_  vmx_2_06  = {};
  inline constexpr vmx_2_07_  vmx_2_07  = {};
  inline constexpr vmx_3_00_  vmx_3_00  = {};
  inline constexpr vmx_3_01_  vmx_3_01  = {};
  inline constexpr vsx_       vsx       = {};
  inline constexpr vsx_2_06_  vsx_2_06  = {};
  inline constexpr vsx_2_07_  vsx_2_07  = {};
  inline constexpr vsx_3_00_  vsx_3_00  = {};
  inline constexpr vsx_3_01_  vsx_3_01  = {};

  // clang-format on
  //================================================================================================
  // PPC ABI concept
  //================================================================================================
  template<typename T> concept ppc_abi = detail::is_one_of<T>(detail::types<ppc_> {});
  template<typename T> concept ppc_tag = requires(T) { typename T::is_ppc; };
}
