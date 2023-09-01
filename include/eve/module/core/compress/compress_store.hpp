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
//!   @warning you should use eve::compress_copy if possible, it has more opportunities
//!   for optimizations.
//!
//!   If this function is not what you are looking for, maybe eve::compress will be help.
//!
//!   You can think about this function as `std::copy_if` for `simd_value`.
//!   Similar to `std::copy_if`, it returns you a `ptr` after the last written element.
//!
//!   There are 2 versions: `unsafe` and `safe`:
//!     * `unsafe` is allowed to write up to `simd_value::size()` elements
//!       regardless of how many elements are selected. In other words it
//!       is eve::compress + eve::store.
//!     * `safe` version will write exactly how many elements are selected.
//!       This makes it slow on most platforms.
//!
//!   @note `safe` version does not touch not selected elements. So, for example,
//!   other threads can read/write them without a race condition.
//!
//!   ## Masked Calls
//!
//!   You can pass eve::relative_conditional_expr ignore modifier to indicate that
//!   some elements should not be considered.
//!
//!   Passing `ignore` other than eve::ignore_none to `unsafe(compress_store)`
//!   converts it into `safe`.
//!
//!   Ignored elements are treated as not selected when compressing.
//!   We start writing from `c.offset()`. This is the same behaviour as eve::store.
//!
//!   @code
//!   ignore_first(1), [a, b, c, d], (true, true, false, true)
//!   ouput: [_, b, d, _] - here _ indicates previous value that was not modified.
//!   @endcode
//!
//!   @note passing `ignore` other that eve::ignore_none to `unsafe(compress_store)`
//!   is making it `safe`.
//!   As soon as we start not writing some elements, it doesn't cost us extra.
//!   Plus it simplifies writing code for ranges with unequal length.
//!
//!   Ignored elements are treated as not selected when compressing.
//!   We start writing from `c.offset()`.
//!
//!   @code
//!   ignore_first(1), [a, b, c, d], (true, true, false, true)
//!   ouput: [_, b, d, _] - here _ indicates previous value that was not modified.
//!   @endcode
//!
//!   Another explanation:
//!   `unsafe(compress_store[ignore])(x, x != 0)` behaves exactly like `store[ignore]`
//!   if none of the elements are 0s.
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template <simd_value T, logical_simd_value L, simd_compatible_ptr<T> Ptr>
//!      unaligned_t<Ptr> unsafe(compress_store)(T x, L m, Ptr ptr)   // (1)
//!
//!      template <relative_conditional_expr C,
//!               simd_value T,
//!               logical_simd_value L,
//!               simd_compatible_ptr<T> Ptr>
//!      unaligned_t<Ptr> unsafe(compress_store[C ignore])(T x, L m, Ptr ptr)   // (2)
//!
//!      template <simd_value T, logical_simd_value L, simd_compatible_ptr<T> Ptr>
//!      unaligned_t<Ptr> safe(compress_store)(T x, L m, Ptr ptr)   // (3)
//!
//!      template <relative_conditional_expr C,
//!               simd_value T,
//!               logical_simd_value L,
//!               simd_compatible_ptr<T> Ptr>
//!      unaligned_t<Ptr> safe(compress_store[C ignore])(T x, L m, Ptr ptr)   // (4)
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`:  `simd_value` to compress
//!      * `m`: mask indicating selected elements
//!      * `ptr`: pointer-like where to write the elements
//!      * `ignore` - optional `eve::relative_condiation_expr`, see detailed explanation above
//!
//!    **Return value**
//!
//!      * ptr after the last selected element written
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/compress/compress_store.cpp}
//!
//! @}
//================================================================================================

EVE_MAKE_CALLABLE(compress_store_, compress_store);
}

#include <eve/module/core/compress/simd/common/compress_store.hpp>
