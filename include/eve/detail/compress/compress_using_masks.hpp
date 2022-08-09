//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/implementation.hpp>

// compress_using_masks
//
// This is an implementation of compress, using masks

namespace eve
{
  EVE_REGISTER_CALLABLE(compress_using_masks_)
  EVE_DECLARE_CALLABLE(compress_using_masks_, compress_using_masks)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(compress_using_masks_, compress_using_masks);
  }

  EVE_CALLABLE_API(compress_using_masks_, compress_using_masks)
}

// compress_using_masks helpers -------------------------------------

namespace eve
{
  EVE_REGISTER_CALLABLE(compress_using_masks_shuffle_)
  EVE_DECLARE_CALLABLE(compress_using_masks_shuffle_, compress_using_masks_shuffle)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(compress_using_masks_shuffle_, compress_using_masks_shuffle);
  }

  EVE_CALLABLE_API(compress_using_masks_shuffle_, compress_using_masks_shuffle)
}

namespace eve
{
  EVE_REGISTER_CALLABLE(compress_using_masks_to_left_)
  EVE_DECLARE_CALLABLE(compress_using_masks_to_left_, compress_using_masks_to_left)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(compress_using_masks_to_left_, compress_using_masks_to_left);
  }

  EVE_CALLABLE_API(compress_using_masks_to_left_, compress_using_masks_to_left)
}

#include <eve/detail/compress/simd/common/compress_using_masks.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/compress/simd/x86/compress_using_masks.hpp>
#endif
