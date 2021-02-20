//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018-2021 Joel FALCOU
  Copyright 2018-2021 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/implementation.hpp>

namespace eve
{
  EVE_DECLARE_CALLABLE(basic_swizzle_)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(basic_swizzle_, basic_swizzle);
  }

  EVE_CALLABLE_API(basic_swizzle_, basic_swizzle)
}

#include <eve/detail/function/simd/common/swizzle.hpp>

#if defined(EVE_HW_X86)
#  include <eve/detail/function/simd/x86/swizzle.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/detail/function/simd/ppc/swizzle.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/detail/function/simd/arm/neon/swizzle.hpp>
#endif
