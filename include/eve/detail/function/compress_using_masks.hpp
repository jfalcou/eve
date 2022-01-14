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

#include <eve/detail/function/simd/common/compress_using_masks.hpp>
