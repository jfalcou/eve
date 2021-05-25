//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(log_, log);
}

#include <eve/module/real/math/function/regular/generic/log.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/math/function/regular/simd/x86/log.hpp>
#endif
