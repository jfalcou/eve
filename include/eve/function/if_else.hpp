//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(if_else_, if_else);
}

#include <eve/arch.hpp>
#include <eve/module/core/function/regular/generic/if_else.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/regular/simd/x86/if_else.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/regular/simd/ppc/if_else.hpp>
#endif

