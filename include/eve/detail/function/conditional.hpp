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
#include <eve/conditional.hpp>
#include <eve/detail/function/simd/common/conditional.hpp>

#if defined(EVE_HW_X86)
// TODO: AVX512 will probably uses special optimisation for the ignore conditional
//#  include <eve/detail/function/simd/x86/conditional.hpp>
#endif
