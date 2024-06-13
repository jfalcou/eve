//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/traits/overload.hpp>

namespace eve
{
  template<typename Options>
  struct byte_swap_pairs_t : callable<byte_swap_pairs_t, Options>
  {
    template<unsigned_value T, std::ptrdiff_t I0, std::ptrdiff_t I1>
    EVE_FORCEINLINE T operator()(T a, index_t<I0> const & i0,  index_t<I1> const & i1) const noexcept
    { return EVE_DISPATCH_CALL(a, i0, i1); }

    EVE_CALLABLE_OBJECT(byte_swap_pairs_t, byte_swap_pairs_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_swap_pairs
//!   @brief swap chosen pairs of bytes in each vector element.
//!
//!   **Defined in Header**
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
//!      template<unsigned_value T, std::ptrdiff_t I0, std::ptrdiff_t I1>
//!      T byte_swap_pairs(T x, , index_t<I0> const & i0, index_t<I1> const & i1) noexcept;
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::integral_value).
//!     * `i0` : first index
//!     * `i1` : second index
//!
//!    **Return value**
//!
//!    Return x byte i0 and i1 swapped in each element of x.
//!    Assert if i0 or i1 are out of range.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/byte_swap_pairs.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::byte_swap_pairs[mask](x, ...)` provides a masked
//!     version of `byte_swap_pairs` which is
//!     equivalent to `if_else(mask, byte_swap_pairs(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto byte_swap_pairs = functor<byte_swap_pairs_t>;

}

#include <eve/module/core/regular/impl/byte_swap_pairs.hpp>
