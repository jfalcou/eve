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
  //!   @var bit_ceil
  //!   @brief Computes the smallest integral power of two that is not smaller than `x`.
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
  //!      template< eve::real_value T >
  //!      T bit_ceil(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!    **Return value**
  //!
  //!    The value of the smallest integral power of two that is not smaller than `x`
  //!    is returned.
  //!
  //!   If that value is not representable in `T`, the behavior is undefined.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/bit_ceil.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::bit_ceil[mask](x, ...)` provides a masked
  //!     version of `bit_ceil` which is
  //!     equivalent to `if_else(mask, bit_ceil(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/bit_ceil.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(bit_ceil_, bit_ceil);
}

#include <eve/module/core/regular/impl/bit_ceil.hpp>
