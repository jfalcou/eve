//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/fnms.hpp>
#include <eve/module/real/core/function/numeric/generic/fnms.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/real/core/function/numeric/simd/x86/fnms.hpp>
#endif
