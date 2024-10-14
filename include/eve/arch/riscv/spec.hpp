//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/riscv/predef.hpp>

#include <cstddef>

//==================================================================================================
// Register count
//==================================================================================================

namespace eve
{
  struct register_count
  {
    static constexpr std::size_t general = 32;
    static constexpr std::size_t simd    = 32;
  };
}

//==================================================================================================
// RVV SIMD ABI
//==================================================================================================
#include <riscv_vector.h>

#define EVE_CURRENT_ABI   ::eve::riscv_
#define EVE_CURRENT_API   ::eve::rvv_
#define EVE_ABI_NAMESPACE riscv_abi_namespace
