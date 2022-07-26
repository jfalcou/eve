//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/wasm/predef.hpp>

#include <cstddef>
#include <cstdint>

//==================================================================================================
// WASM Info
#if defined(EVE_HW_WASM)
namespace eve
{
struct register_count
{
  static constexpr std::size_t general = 2 * sizeof(void *);
  static constexpr std::size_t simd    = 2 * sizeof(void *);
};
}

//==================================================================================================
// WASM SIMD API/ABI
#  if !defined(EVE_CURRENT_API) && defined(SPY_SIMD_IS_WASM)
#    include <wasm_simd128.h>
#    define EVE_ABI_DETECTED
#    define EVE_CURRENT_ABI   ::eve::wasm_128_
#    define EVE_CURRENT_API   ::eve::simd128_
#    define EVE_ABI_NAMESPACE wasm128_abi_v0
#  endif

#endif
