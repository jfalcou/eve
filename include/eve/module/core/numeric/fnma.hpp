//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/numeric/impl/fnma.hpp>
#include <eve/module/core/regular/fnma.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/numeric/impl/simd/x86/fnma.hpp>
#endif
