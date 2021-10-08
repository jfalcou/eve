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
  EVE_REGISTER_CALLABLE(sum_)
  EVE_DECLARE_CALLABLE(sum_, sum)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(sum_, sum);
  }

  EVE_CALLABLE_API(sum_, sum)
}

#include <eve/detail/function/simd/common/sum.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/sum.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/detail/function/simd/arm/neon/sum.hpp>
#endif
