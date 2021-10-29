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

// compress_store_impl
// Writes all compressed values to the provided pointer
// Unlike a real compress store, offset of ignore won't move values.
//
// Example:
//   [a b c d], [true, true, true, true], ignore_first(1)
//  compress_store     : [ _ b c d]
//  compress_store_impl: [b c d _ ]

namespace eve
{
  EVE_REGISTER_CALLABLE(compress_store_impl_)
  EVE_DECLARE_CALLABLE(compress_store_impl_, compress_store_impl)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(compress_store_impl_, compress_store_impl);
  }

  EVE_CALLABLE_API(compress_store_impl_, compress_store_impl)
}

#include <eve/detail/function/simd/common/compress_store_impl.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/compress_store_impl.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#    include <eve/detail/function/simd/arm/neon/compress_store_impl.hpp>
#endif
