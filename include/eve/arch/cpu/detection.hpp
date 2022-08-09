//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/cpu/tags.hpp>

namespace eve
{
  //================================================================================================
  // Runtime detection of CPU support
  inline bool is_supported(cpu_ const &) noexcept { return true; }
}
