//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/soa_ptr.hpp>

#include <cstddef>
#include <string_view>

#define EVE_TEST_STRINGIFY_(x) #x
#define EVE_TEST_STRINGIFY(x)  EVE_TEST_STRINGIFY_(x)

namespace abi_test
{
  inline constexpr std::ptrdiff_t lanes = 16;

  // Defined in native.cpp, compiled for the current platform
  std::string_view native_abi_namespace();
  bool             native_supports_simd();
  void             square(eve::aligned_ptr<float, lanes> data, std::ptrdiff_t size);
  int              dot(eve::soa_ptr<int const*, int const*> data, std::ptrdiff_t size);
}
