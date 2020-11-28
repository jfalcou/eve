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

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(store_, store);
}

#include <eve/module/core/function/regular/generic/store.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/regular/simd/x86/store.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/regular/simd/ppc/store.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/regular/simd/arm/neon/store.hpp>
#endif

