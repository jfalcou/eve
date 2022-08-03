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
  //!   @var bit_mask
  //!   @brief Computes a bit mask full of zeroes or ones
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
  //!      T bit_mask(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [argument](@ref eve::value).
  //!
  //!    **Return value**
  //!
  //!      For each [elementwise](@ref glossary_elementwise) of `x`:
  //!
  //!        *  if the [element](@ref glossary_elementwise) is zero, an element
  //!           with all bits unset is returned.
  //!        *  else an element of the type with all bits set is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/bit_mask.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::bit_mask[mask](x)` provides a masked
  //!     version of `bit_mask` which is
  //!     equivalent to `if_else(mask, bit_mask(x), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/bit_mask.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(bit_mask_, bit_mask);
}

#include <eve/module/core/regular/impl/bit_mask.hpp>
