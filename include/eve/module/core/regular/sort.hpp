//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct sort_t : callable<sort_t, Options>
  {
    template<eve::simd_value T, typename Less>
    constexpr EVE_FORCEINLINE T operator()(T v, Less l) const noexcept
    { return EVE_DISPATCH_CALL(v, l); }

     template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sort_t, sort_);
  };
// TODO DOC
//================================================================================================
//! @addtogroup core_simd
//! @{
//!   @var sort
//!   @brief sorts a register in a accedning order accroding to a comparator.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   Sorting algorithm, based on sortin networks.
//!
//!   @note this sort is unstable.
//!
//!   Also our implementation is not directly based on any specific one,
//!   people we are definetly not the first people to do this.
//!   Here is a list of previous work that was looked at.
//!    * A Novel Hybrid Quicksort Algorithm Vectorized using AVX-512 on
//!      Intel Skylake: arXiv:1704.08579
//!    * damageboy (and his github)
//!      https://bits.houmus.org/2020-01-28/this-goes-to-eleven-pt1
//!    * Berenger Bramas
//!      A fast vectorized sorting implementation based on the ARM scalable vector extension
//!      https://www.researchgate.net/publication/351656348_A_fast_vectorized_sorting_implementation_based_on_the_ARM_scalable_vector_extension_SVE
//!    * Intel x86-simd-sort
//!      https://github.com/intel/x86-simd-sort
//!    * Google's: Vectorized and performance-portable Quicksort
//!      Mark Blacher, Joachim Giesen, Peter Sanders, Jan Wassenberg
//!      https://opensource.googleblog.com/2022/06/Vectorized%20and%?20performance%20portable%20Quicksort.html
//!    * A Question of Sorts
//!      http://seven-degrees-of-freedom.blogspot.com/2010/07/question-of-sorts.html
//!    * Kyle Hegeman (`@khegeman`)
//!      https://github.com/khegeman/floki
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overloads
//!      constexpr auto sort(value auto  x);                    noexcept; // 1
//!      constexpr auto sort(value auto  x, ordering auto less) noexcept; // 1
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * x - simd_value to sort
//!     * less - simd strict weak ordering. Defaults to eve::is_less.
//!
//!   **Return value**
//!
//!     1. sorted x.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/sort.cpp}
//!
//! @}
//================================================================================================
  inline constexpr auto sort = functor<sort_t>;

  namespace detail
  {
    // Building up, then going down.
    // 0, 1, 1, 0, 0, 1, 1, 0 ...
    template <std::ptrdiff_t Full>
    constexpr auto bitonic_merge_blend_pattern = [](int i, int) {
      int turn = i / Full;
      bool is_odd_turn = turn % 2;
      return (i + is_odd_turn) % 2;
    };

    template <typename T, typename Less, std::ptrdiff_t Full, std::ptrdiff_t G>
    constexpr EVE_FORCEINLINE
    T bitonic_merge_impl(T x, Less less, fixed<Full> full, fixed<G> g) noexcept
    {
      if constexpr ( G == 0 ) return x;
      else
      {
        T ab = x;
        T ba = eve::swap_adjacent(ab, g);
        auto [aa, bb] = minmax(less)(ab, ba);
        x = blend(aa, bb, g, bitonic_merge_blend_pattern<Full / G>);
        return bitonic_merge_impl(x, less, full, lane<G / 2>);
      }
    }

    // G is the length of the monotonic sequence
    template <typename T, typename Less, std::ptrdiff_t G>
    constexpr EVE_FORCEINLINE
    T bitonic_merge(T x, Less less, fixed<G>) noexcept
    {
      return bitonic_merge_impl(x, less, lane<G * 2>, eve::lane<G>);
    }

    // G - length of monotonic sequence
    template <simd_value T, typename Less, std::ptrdiff_t G>
    constexpr EVE_FORCEINLINE
    T make_bitonic(T x, Less less, fixed<G>) noexcept
    {
      if constexpr (G < 1)
        return x;
      else
      {
        x = make_bitonic(x, less, lane<G / 2>);
        return bitonic_merge(x, less, lane<G / 2>);
      }
    }

    template <typename T, typename Less, callable_options O>
    constexpr EVE_FORCEINLINE
    T sort_(EVE_REQUIRES(cpu_), O const &, T x, Less less) noexcept
    {
      return make_bitonic(x, less, eve::lane<T::size()>);
    }

    template <typename T, callable_options O>
    constexpr EVE_FORCEINLINE
    T sort_(EVE_REQUIRES(cpu_), O const &, T x) noexcept
    {
      return sort(x, eve::is_less);
    }
  }
}
