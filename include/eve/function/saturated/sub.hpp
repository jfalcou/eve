//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/sub.hpp>
#include <eve/module/real/core/function/saturated/generic/sub.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/saturated/simd/x86/sub.hpp>
#endif
