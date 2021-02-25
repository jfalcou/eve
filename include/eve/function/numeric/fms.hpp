//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/fms.hpp>
#include <eve/module/real/core/function/numeric/generic/fms.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/real/core/function/numeric/simd/x86/fms.hpp>
#endif
