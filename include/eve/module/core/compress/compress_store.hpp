//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_compress
//! @{
//!   @var compress_store
//!   @brief A function that stores selected elements from an eve::simd_value
//!   to an eve::simd_compatible_ptr, while compressing them to the beginning.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   This function behaves like eve::compress_copy[dense] but as input it takes
//!   loaded register. @see eve::compres_copy for explained behavour.
//!
//!   @warning you should use eve::compress_copy if possible, it has more opportunities
//!   for optimizations.
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template <relative_conditional_expr C1,
//!                relative_conditional_expr C2,
//!                simd_value T,
//!                logical_simd_value L,
//!                typename O>
//!      auto compress_store
//!          [safe/unsafe]
//!          [C1 ignore_in][C2 ignore_out]
//!          (T x, L m, O o)  -> unaligned_t<O> // (1)
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * safe/unsafe - mode of the operation - required
//!      * ignore_in - optional, ignored elements considered not selected.
//!      * ignore_out - optional, defaults to ignore_in.
//!                     controls part of the output where the data will be written.
//!      * `x`:  `simd_value` to compress
//!      * `m`: mask indicating selected elements
//!      * `o`: pointer-like where to write the elements
//!
//!    **Return value**
//!
//!      * o after the last selected element written
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/compress/compress_store.cpp}
//!
//! @}
//================================================================================================
}

#include <eve/module/core/compress/simd/common/compress_store.hpp>
