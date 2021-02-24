//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/add.hpp>
#include <eve/module/real/core/function/saturated/generic/add.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/real/core/function/saturated/simd/x86/add.hpp>
#endif
