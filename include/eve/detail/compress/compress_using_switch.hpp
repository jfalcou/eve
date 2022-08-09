//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/implementation.hpp>

// compress_using_switch
//
// This is an implementation of `compress` for sse2 only.

namespace eve
{
  EVE_REGISTER_CALLABLE(compress_using_switch_)
  EVE_DECLARE_CALLABLE(compress_using_switch_, compress_using_switch)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(compress_using_switch_, compress_using_switch);
  }

  EVE_CALLABLE_API(compress_using_switch_, compress_using_switch)
}

#include <eve/detail/compress/simd/common/compress_using_switch.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/compress/simd/x86/compress_using_switch.hpp>
#endif
