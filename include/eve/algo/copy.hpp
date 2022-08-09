//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/algo/common_forceinline_lambdas.hpp>
#include <eve/algo/traits.hpp>
#include <eve/algo/transform.hpp>
#include <eve/algo/views/backward.hpp>
#include <eve/algo/views/zip.hpp>

namespace eve::algo
{
  template <typename TraitsSupport>
  struct copy_ : TraitsSupport
  {
    template <zipped_range_pair R>
    EVE_FORCEINLINE void operator()(R r) const
    {
      return transform_to[TraitsSupport::get_traits()](r, do_nothing{});
    }

    template <typename R1, typename R2>
    requires zip_to_range<R1, R2>
    EVE_FORCEINLINE void operator()(R1&& r1, R2&& r2) const
    {
      operator()(views::zip(EVE_FWD(r1), EVE_FWD(r2)));
    }
  };

  //================================================================================================
  //! @addtogroup algos
  //! @{
  //!   @var copy
  //!   @brief SIMD optimized copy algorithm
  //!
  //!   Configurable @callable performing a SIMD optimized version of the copy.
  //!   By default, the operation will be unrolled by a factor of 4, align memory accesses and
  //!   perform conversions if needed.
  //!
  //!   @note If you want to copy elements of same scalar type, use `std::memmove`.
  //!
  //!   **Alternative Header**
  //!
  //!   @code
  //!   #include <eve/algo.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve::algo
  //!   {
  //!     template<typename R1, typename R2>
  //!     void copy(R1&& r1, R2&& r2) requires zip_to_range<R1, R2>;    //  1
  //!
  //!     void copy(zipped_range_pair auto&& r);                        //  2
  //!   }
  //!   @endcode
  //!
  //!   1. Copy the elements of from `r1` to  `r2`.
  //!   2. Copy the elements of from `get<0>(r)` to `get<1>(r)`.
  //!
  //!   **Parameters**
  //!
  //!     * `r1` : The range of elements or an iterator to the beginning of the elements to copy from
  //!     * `r2` : A range or an iterator to the beginning of the destination elements
  //!     * `r`  : An eve::algo::zipped_range_pair of ranges and/or iterators.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/algo/copy.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto copy = function_with_traits<copy_>[default_simple_algo_traits];

  template <typename TraitsSupport>
  struct copy_backward_ : TraitsSupport
  {
    template <zipped_range_pair R>
    EVE_FORCEINLINE void operator()(R r) const
    {
      auto [from, to] = r;
      return copy[TraitsSupport::get_traits()](views::backward(from), views::backward(to));
    }

    template <typename R1, typename R2>
    requires zip_to_range<R1, R2>
    EVE_FORCEINLINE void operator()(R1&& r1, R2&& r2) const
    {
      static_assert(!relaxed_iterator<R2>, "Behavior of std::copy_backward and eve::algo::copy_backward"
                                           " would differ for a second parameter iterator."
                                           " Use eve::algo::copy_backward(zip(r, it))"
                                           " or pass a range as a second parameter.");
      operator()(views::zip(EVE_FWD(r1), EVE_FWD(r2)));
    }
  };

  //================================================================================================
  //! @addtogroup algos
  //! @{
  //!   @var copy_backward
  //!   @brief SIMD optimized backward copy algorithm
  //!
  //!   Configurable @callable performing backward copy between two ranges' or between a range and
  //!   an iterator.
  //!
  //!   By default, eve::algo::copy_backward will be unrolled by a factor of 4, align memory
  //!   accesses and perform conversions if needed.
  //!
  //!   @note If you want to copy between ranges of the same scalar type, use `std::memmove`.
  //!
  //!   **Alternative Header**
  //!
  //!   @code
  //!   #include <eve/algo.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve::algo
  //!   {
  //!     template<typename R1, typename R2>
  //!     void copy_backward(R1&& r1, R2&& r2) requires zip_to_range<R1, R2>;    //  1
  //!
  //!     void copy_backward(zipped_range_pair auto&& r);                        //  2
  //!   }
  //!   @endcode
  //!
  //!   1. Copy the elements of from `r1` to  `r2`.
  //!   2. Copy the elements of from `get<0>(r)` to `get<1>(r)`.
  //!
  //!   The elements are copied in reverse order (the last element is copied first), but their
  //!   relative order is preserved. Due to the specificities of the SIMD algorithm, the second
  //!   can not be an iterator. Use the zip based overload to do so.
  //!
  //!   **Parameters**
  //!
  //!     * `r1` : The range of elements or an iterator to the beginning of the elements to copy from
  //!     * `r2` : A range of the destination elements
  //!     * `r` : A eve::algo::zipped_range_pair of ranges and/or iterators.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/algo/copy_backward.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto copy_backward = function_with_traits<copy_backward_>[default_simple_algo_traits];
}
