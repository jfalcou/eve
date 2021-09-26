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

// compress_store_unsafe_switch
//
// The very simple switch based solution.
// Is the only option when we can't shuffle with a mask.

namespace eve
{
  EVE_REGISTER_CALLABLE(compress_store_unsafe_switch_);
  EVE_DECLARE_CALLABLE(compress_store_unsafe_switch_, compress_store_unsafe_switch);

  namespace detail
  {
    EVE_ALIAS_CALLABLE(compress_store_unsafe_switch_, compress_store_unsafe_switch);
  }

  EVE_CALLABLE_API(compress_store_unsafe_switch_, compress_store_unsafe_switch)
}

#include <eve/detail/function/simd/common/compress_store_unsafe_switch.hpp>
