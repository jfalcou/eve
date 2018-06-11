//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
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
