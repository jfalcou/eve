//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/implementation.hpp>

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
