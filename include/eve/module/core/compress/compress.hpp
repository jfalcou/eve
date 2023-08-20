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

// compress
//
// A working horse for compress_store.
//
// Inputs: an ignore, a wide and a mask.
//
// Splits the input wide into parts that we can efficiently compute.
// compresses the individual parts (everything marked as true is moved to the left).
// returns a tuple of results for individual chunks.
// A result for individual chunk is again - a tuple [ compressed_value, number of elements ]

namespace eve
{
  EVE_MAKE_CALLABLE(compress_, compress);
}

#include <eve/module/core/compress/simd/common/compress.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/compress/simd/x86/compress.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/compress/simd/arm/sve/compress.hpp>
#endif
