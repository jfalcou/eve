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
// The idea from: https://gist.github.com/aqrit/6e73ca6ff52f72a2b121d584745f89f3#file-despace-cpp-L141
// Was shown to me by: @aqrit
// Stack Overflow discussion: https://chat.stackoverflow.com/rooms/212510/discussion-between-denis-yaroshevskiy-and-peter-cordes
//
// For compress stores implemented as a swizzle, extracted logic
// to compute a number of the mask.
//
// Depending on the number of elements, this is a different number
// and a different extra information.
//
// 4 elements
// ================
// For 4 elements we do a complete shuffle of the first 3 elements
// 4 elements version also accepts ignore (none of the others do).
// the last one is always written.
// We also return a bool if the last element is set.
// (compiler will optimize that computation away,
// if the caller just calls popcount and not use it).
//
// Example:
//   mask:            [ false, true, false, false]
//   shuffle we want: [     1,    3,     _,     _]
//   the number of the shuffle is 0100 -> 2
//   is last set:     false
//
// 8 elements.
// ==================
// In compress store we first do << 1 and if_else(mask, x, slide_left(x, 1));
// This reduces variativity.
// Last 2 elements are OK to store.
// For all previous pairs we reduce the number of options from 4 to 3.
// [0, 0], [1, 0] and [0, 1], [1, 1].
//
// This means we have 3 * 3 * 3 options.
// The easiest way to convert from a mask to a 27 options is to interpet it
// as a base3 number: each 2 elements are a base 3 digit.
// This is a popcount for 2 elements.
// We also return popcount.
//
// 16 elements
// ==================
// 16 elements are twice 8 but sometimes we can do them faster.
// Returns {num, count} twice for both halves.
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
