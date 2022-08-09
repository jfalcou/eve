//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/implementation.hpp>

// Based on: https://stackoverflow.com/a/36951611/5021064
// Explanation (a bit outdated): https://stackoverflow.com/a/61431303/5021064
// Mask functions return the compressed indexes and the popcount.
//
// Credit for the idea goes to @PeterCordes

namespace eve
{
  EVE_REGISTER_CALLABLE(compress_using_bmi_)
  EVE_DECLARE_CALLABLE(compress_using_bmi_, compress_using_bmi)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(compress_using_bmi_, compress_using_bmi);
  }

  EVE_CALLABLE_API(compress_using_bmi_, compress_using_bmi)
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/compress/simd/x86/compress_using_bmi.hpp>
#endif
