//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/rsqrt.hpp>
#include <eve/module/real/core/function/pedantic/generic/rsqrt.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/pedantic/simd/x86/rsqrt.hpp>
#endif
