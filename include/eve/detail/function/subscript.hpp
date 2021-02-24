//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/function/simd/common/subscript.hpp>

#if defined(EVE_HW_X86)
#  include <eve/detail/function/simd/x86/subscript.hpp>
#endif
