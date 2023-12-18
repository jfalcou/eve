//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_simd
//! @{
//!   @var sort
//!   @brief sorts a register in a accedning order accroding to a comparator.
//!
//!   **Defined in Header**
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
//!     template <simd_value T, typename Less>
//!     T sort(T x, Less less);               // (1)
//!
//!     template <simd_value T>
//!     T sort(T x);                          // (2)
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   * x - simd_value to sort
//!   * less - simd strick weak ordering. Defaults to eve::is_less.
//!
//!  **Return value**
//!
//!  sorted x.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/sort.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(sort_, sort);
}

#include <eve/module/core/regular/impl/sort.hpp>
