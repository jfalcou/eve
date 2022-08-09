//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/sub.hpp>
#include <eve/module/core/saturated/impl/sub.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/saturated/impl/simd/x86/sub.hpp>
#endif
