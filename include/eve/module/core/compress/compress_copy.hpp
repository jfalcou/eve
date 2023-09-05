//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve
{

//================================================================================================
//! @addtogroup core_compress
//! @{
//!    @var compress_copy
//!    @brief A function that copies selected elements from source to destination,
//!    while compressing them to the left.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   If this function doesn't work for you, maybe you are looking for eve::comress_store or
//!   eve::compress. However this function is faster.
//!
//!   You can think about this function as `std::copy_if` but instead of a predicate,
//!   you pass in logical_simd_value. Similar to `std::copy_if` it returns you
//!   a pointers to where the output ended.
//!   @note: you might be missing information about the last selected element written,
//!   but unfortunately that adds overhead we couldn't fix (#1656)
//!
//!   There are the following two modifiers:
//!     * safe/unsafe - unsafe version is allowed to write up to `mask.size()` elements,
//!                     even if not all are selected. Those values are undefined.
//!                     safe is not allowed to perform those writes, at the price of
//!                     being slower for certain usecases.
//!     * dense/sparse - wether or not you expect a lot of selected elements.
//!
//!   @note `safe` version does not touch not selected elements. So, for example,
//!   other threads can read/write them without a race condition.
//!
//!   ## Preloaded values
//!
//!   Very often the mask is computed based on the values loaded from input.
//!   We would expect the optimizer to eliminate duplicated loads,
//!   but for some very complex pointer-like it might not be able to.
//!
//!   So we provide overloads where you can pass an already preloaded value. It should
//!   match loaded value from in, otherwise the behaviour is unspecified.
//!
//!   ## Masked Calls
//!
//!   You can pass up to two eve::relative_conditional_expr ignore modifiers.
//!   1st is the input side ignore:
//!     * the ignored elements can are not loaded (same as load[ignore])
//!     * they are treated as not selected, regardless of the mask value
//!   2nd is the output side ignore:
//!     * elements that are ignored, will not be written.
//!       having initial offset is equvialent to offeting the `o + offset`.
//!       followed by keep_first(count)
//!     Example:
//!       if the `eve::ignore_extrema(1, L::size() - 2)` is passed,
//`       the first selected element will be written at o + 1.
//!     Defaults to 1st ignore.
//!
//!   If the mask == true this and it's `unsafe` variation, this is the same behaviour as
//!
//!   @code
//!   // start with + offset
//!   in += ignore_in.offset(eve::as(m));
//!   out += ignore_out.offset(eve::as(m));
//!
//!   eve::keep_first ignore_in1(ignore_in.count(eve::as(m)));
//!   eve::keep_first ignore_out1(ignore_out.count(eve::as(m)));
//!
//!   // load + store
//!   auto x = eve::load[ignore_in1](in);
//!   eve::store[ignore_out1](x, out);
//!   @endcode
//!
//!   For safe behaviour, we'd also have to make sure not to write not selected elements.
//!
//!   @groupheader{Callable Signatures}
//!
//!   @note - no proper concept for input and output, these are pointer like things,
//!           but `eve::algo::iterator` also work here. FIX-1652
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
//!      auto compress_copy
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
//!      auto compress_copy
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
//!      * `safe/unsafe` - required - variations described above.
//!      * `sparse/dense` - optional - default to `dense`. described above.
//!      * `ignore_in` - optional (default - ignore_none) - ignored elements are treated as not selected.
//!      * `ignore_out` - optional (default - ignore_in) - ignored elements are not written to in the output.
//!      * `in`: input ptr-like from which to copy
//!      * `m`: mask indicating selected elements
//!      * `out`: output to  will write elements
//!
//!   **Return value**
//!
//!      * unaligned_t<O> where result - out == number of elements written
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/compress/compress_copy.cpp}
//! @}
//================================================================================================

}

#include <eve/module/core/compress/simd/common/compress_copy.hpp>
