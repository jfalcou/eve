//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/wasm/tags.hpp>
#include <eve/detail/spy.hpp>

namespace eve
{
//==================================================================================================
// Runtime detection of CPU support
//==================================================================================================
template<auto Version>
inline bool is_supported(spy::wasm_simd_info<Version> const&) noexcept
{
#if defined(EVE_HW_WASM)
  return true;
#else
  return false;
#endif
}
}
