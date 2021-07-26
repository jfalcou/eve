//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/implementation.hpp>

namespace eve
{
  EVE_REGISTER_CALLABLE(basic_swizzle_)
  EVE_DECLARE_CALLABLE(basic_swizzle_, basic_swizzle)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(basic_swizzle_, basic_swizzle);
  }

  EVE_CALLABLE_API(basic_swizzle_, basic_swizzle)
}

#include <eve/detail/function/simd/common/swizzle.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/swizzle.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/detail/function/simd/ppc/swizzle.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/detail/function/simd/arm/neon/swizzle.hpp>
#endif
