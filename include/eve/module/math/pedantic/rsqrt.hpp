//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/math/regular/rsqrt.hpp>
#include <eve/module/math/pedantic/impl/rsqrt.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/math/pedantic/impl/simd/x86/rsqrt.hpp>
#endif
