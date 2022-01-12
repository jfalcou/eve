//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic/regular/fnma.hpp>
#include <eve/module/arithmetic/pedantic/impl/fnma.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/arithmetic/pedantic/impl/simd/x86/fnma.hpp>
#endif
