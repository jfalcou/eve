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
//! @addtogroup core_bitops
//! @{
//!   @var bit_reverse
//!   @brief  elementwise reverse the bit order.
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
//!      template< eve::value T >
//!      T bit_reverse(T x) noexcept;                                         //1
//!      template< eve::value T auto N>
//!      T bit_reverse(T x
//!                    , std::integral_constant<size_tN> const & n) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!     * `n` :  n delimit the band to be reversed at both ends of x
//!
//!    **Return value**
//!
//!    The values of the of the parameter are returned with bits in reversed order.
//!    if n is present :
//!      - if n == 0 the call returns x
//!      - if 2*n >= sizeof(element_type_t<T>)   the call is identical to reverse(x)
//!      - otherwise the first n bits and the last n bits of each element of x are swapped in
//!        reverse order and the central remaining bits are unchanged.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_reverse.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_reverse[mask](x, ...)` provides a masked
//!     version of `bit_reverse` which is
//!     equivalent to `if_else(mask, bit_reverse(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_reverse.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bit_reverse_, bit_reverse);
}

#include <eve/module/core/regular/impl/bit_reverse.hpp>
