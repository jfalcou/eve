//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/fma.hpp>
#include <eve/module/real/core/function/pedantic/generic/fma.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/real/core/function/pedantic/simd/x86/fma.hpp>
#endif
