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
  template<typename Options>
  struct swap_pairs_t : callable<swap_pairs_t, Options>
  {
    template<simd_value T, std::ptrdiff_t I0, std::ptrdiff_t I1>
    EVE_FORCEINLINE T operator()(T x, index_t<I0> i0, index_t<I1> i1) const noexcept
    {
      return EVE_DISPATCH_CALL(x, i0, i1);
    }

    EVE_CALLABLE_OBJECT(swap_pairs_t, swap_pairs_);
  };

  //TODO DOC
  //================================================================================================
  //! @addtogroup core_bitops
  //! @{
  //!   @var swap_pairs
  //!   @brief swap chosen pair of elements.
  //!
  //!   @groupheader{Header file}
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template<simd_value T, std::ptrdiff_t I0, std::ptrdiff_t I1 >
  //!      T swap_pairs(T x, index_t<I0> const & i0, index_t<I1> const & i1);
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [argument](@ref eve::simd_value).
  //!     * `i0` : first index
  //!     * `i1` : second index
  //!
  //!    **Return value**
  //!
  //!    Return x with element i0 and i1 swapped.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/swap_pairs.cpp}
  //================================================================================================
  inline constexpr auto swap_pairs = functor<swap_pairs_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/module/core/regular/impl/swap_pairs.hpp>
