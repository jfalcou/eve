//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/pedantic/impl/fnms.hpp>
#include <eve/module/core/regular/fnms.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/pedantic/impl/simd/x86/fnms.hpp>
#endif
