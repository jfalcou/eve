//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(is_not_greater_, is_not_greater);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/is_not_greater.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/is_not_greater.hpp>
#endif
