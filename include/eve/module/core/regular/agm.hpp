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
  //! @addtogroup core
  //! @{
  //!   @var agm
  //!   @brief Computes the arithmetic-geometric mean.
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
  //!      template< eve::floating_value T, eve::floating_value U >
  //!      eve::common_compatible_t<T, U> agm(T x, U y) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`:  arguments.
  //!
  //!    **Return value**
  //!
  //!      The value of the arithmetic-geometric mean is returned. No overflow can occur.
  //!      The two parameters must share the same sign.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/agm.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::agm[mask](x, ...)` provides a masked version of `agm` which is
  //!     equivalent to `if_else(mask, agm(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/agm.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(agm_, agm);
}

#include <eve/module/core/regular/impl/agm.hpp>
