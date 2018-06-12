//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_DETAIL_MAKE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_DETAIL_MAKE_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/make.hpp>

#if EVE_HW_X86 >= EVE_SSE2_VERSION
#include <eve/module/core/function/simd/x86/sse2/make.hpp>
#endif

#if EVE_HW_X86 >= EVE_AVX_VERSION
#include <eve/module/core/function/simd/x86/avx/make.hpp>
#endif

#endif
