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

// compress_store_swizzle_mask_num
//
// For compress stores implemented as a swizzle, extracted logic
// to compute a number of the mask.
//
// Depending on the number of elements, this is a different number
// and a different extra information.
//
// For 4 elements we do a complete shuffle of the first 3 elements
// the last one is always written.
// We also return a bool if the last element is set.
// (compiler will optimize that computation away,
// if the caller just calls popcount and not use it).
//
//
// Example:
//   mask:            [ false, true, false, false]
//   shuffle we want: [     1,    3,     _,     _]
//   the number of the shuffle is 0100 -> 2
//   is last set:     false
//

namespace eve
{
  EVE_REGISTER_CALLABLE(compress_store_swizzle_mask_num_);
  EVE_DECLARE_CALLABLE(compress_store_swizzle_mask_num_, compress_store_swizzle_mask_num);

  namespace detail
  {
    EVE_ALIAS_CALLABLE(compress_store_swizzle_mask_num_, compress_store_swizzle_mask_num);
  }

  EVE_CALLABLE_API(compress_store_swizzle_mask_num_, compress_store_swizzle_mask_num)
}

#include <eve/detail/function/simd/common/compress_store_swizzle_mask_num.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/compress_store_swizzle_mask_num.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
# include <eve/detail/function/simd/arm/neon/compress_store_swizzle_mask_num.hpp>
#endif
