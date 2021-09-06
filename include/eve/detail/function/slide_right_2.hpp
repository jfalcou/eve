//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

namespace eve
{
  EVE_MAKE_CALLABLE(slide_right_2_, slide_right_2);
}

#include <eve/detail/function/simd/common/slide_right_2.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/slide_right_2.hpp>
#endif
