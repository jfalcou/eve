//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic/regular/fms.hpp>
#include <eve/module/arithmetic/numeric/impl/fms.hpp>


#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/arithmetic/numeric/impl/simd/x86/fms.hpp>
#endif
