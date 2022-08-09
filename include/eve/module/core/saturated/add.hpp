//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/saturated/impl/add.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/saturated/impl/simd/x86/add.hpp>
#endif
