//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_bitops
  //! @{
  //!   @var bit_floor
  //!   @brief If `x` is not zero, computes the largest integral power of two
  //!   that is not greater than `x`.
  //!
  //!   $details$
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
  //!      T bit_floor(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [argument](@ref eve::value).
  //!
  //!    **Return value**
  //!
  //!      * The value of the largest integral power of two
  //!        that is not greater than `x` is returned.
  //!
  //!      * If `x` is zero returns zero.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/bit_floor.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::bit_floor[mask](x, ...)` provides a masked
  //!     version of `bit_floor` which is
  //!     equivalent to `if_else(mask, bit_floor(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/bit_floor.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(bit_floor_, bit_floor);
}

#include <eve/module/core/regular/impl/bit_floor.hpp>
