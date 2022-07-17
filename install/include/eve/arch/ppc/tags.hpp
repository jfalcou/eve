//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

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
  using vmx_  = simd_api<simd_    , spy::vmx_ >;
  using vsx_  = simd_api<vmx_ , spy::vsx_>;

  //================================================================================================
  //  V*X extension tag objects
  //================================================================================================
  inline constexpr vmx_ vmx = {};
  inline constexpr vsx_ vsx = {};

  // clang-format on
  //================================================================================================
  // PPC ABI concept
  //================================================================================================
  template<typename T> concept ppc_abi = detail::is_one_of<T>(detail::types<ppc_> {});
}
