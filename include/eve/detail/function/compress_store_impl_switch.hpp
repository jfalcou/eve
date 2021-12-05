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

// compress_store_impl_switch
//
// This is an implementation of `compress_store_impl` for sse2 only.

namespace eve
{
  EVE_REGISTER_CALLABLE(compress_store_impl_switch_)
  EVE_DECLARE_CALLABLE(compress_store_impl_switch_, compress_store_impl_switch)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(compress_store_impl_switch_, compress_store_impl_switch);
  }

  EVE_CALLABLE_API(compress_store_impl_switch_, compress_store_impl_switch)
}

#include <eve/detail/function/simd/common/compress_store_impl_switch.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/compress_store_impl_switch.hpp>
#endif
