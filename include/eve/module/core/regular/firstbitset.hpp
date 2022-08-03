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
  //!   @var firstbitset
  //!   @brief Computes [elementwise](@ref glossary_elementwise) the bit pattern
  //!   in which the only bit set (if it exists) is the first bit set in the input.
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
  //!      template< eve::unsigned_value T >
  //!      T firstbitset(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [argument](@ref eve::value).
  //!
  //!    **Return value**
  //!
  //!       Computes [elementwise](@ref glossary_elementwise) the bit pattern in
  //!       which the only bit set (if it exists) is
  //!       the first bit set (beginning with the least significant bit) in the input.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/firstbitset.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::firstbitset[mask](x)` provides a masked
  //!     version of `firstbitset` which is
  //!     equivalent to `if_else(mask, firstbitset(x), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/firstbitset.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(firstbitset_, firstbitset);
}

#include <eve/module/core/regular/impl/firstbitset.hpp>
