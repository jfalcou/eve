//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic/regular/add.hpp>
#include <eve/module/arithmetic/saturated/impl/add.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/arithmetic/saturated/impl/simd/x86/add.hpp>
#endif
