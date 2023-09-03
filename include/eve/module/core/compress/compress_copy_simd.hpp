//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once


//================================================================================================
//! @addtogroup core_compress
//! @{
//!    @var compress_copy_simd
//!    @brief One of the implementations for eve::compress_copy that relies on
//!    only simd shuffles and writes.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @warning you should probably use eve::compress_copy.
//!
//!   eve::compress_copy will either call this or eve::compress_copy_scalar.
//!   We believe eve::compress_copy makes correct selection of which one to use
//!   but this is exposed in case we didn't.
//!
//!   Api completly matches eve::compress_copy.
//!
//!   @note this internally just calls eve::compress_store
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!
//!      template <relative_conditional_expr C1,
//!                relative_conditional_expr C2,
//!                typename I,
//!                logical_simd_value L,
//!                typename O>
//!      autoo compress_copy_simd
//!        [safe/unsafe][sparse/dense]
//!        [C1 ignore_in][C2 ignore_out](
//!           I in,
//!           L mask,
//!           O out) -> unaligned_t<O>;   // (1)
//!
//!      template <relative_conditional_expr C1,
//!                relative_conditional_expr C2,
//!                typename I,
//!                logical_simd_value L,
//!                typename O>
//!      autoo compress_copy_simd
//!        [safe/unsafe][sparse/dense]
//!        [C1 ignore_in][C2 ignore_out](
//!           I in,
//!           wide<value_type_t<I>, fixed<L::size()>> preloaded,
//!           L mask,
//!           O out) -> unaligned_t<O>;   // (2)
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   @see eve::compress_copy
//!
//!   **Return value**
//!
//!   @see eve::compress_copy
//! @}
//================================================================================================

#include <eve/module/core/compress/simd/common/compress_copy_simd.hpp>
