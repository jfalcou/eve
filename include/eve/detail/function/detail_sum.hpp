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
  EVE_REGISTER_CALLABLE(detail_sum_)
  EVE_DECLARE_CALLABLE(detail_sum_, detail_sum)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(detail_sum_, detail_sum);
  }

  EVE_CALLABLE_API(detail_sum_, detail_sum)
}

#include <eve/detail/function/simd/common/detail_sum.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/detail_sum.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/detail/function/simd/arm/neon/detail_sum.hpp>
#endif
