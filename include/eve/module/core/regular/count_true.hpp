/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/arch.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_horizontal
  //! @{
  //!   @var count_true
  //!   @brief Computes the number of non 0 elements
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
  //!      T count_true(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!    **Return value**
  //!
  //!    The value of the number of non 0 elements
  //!    is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/count_true.cpp}
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::$name$[mask](x, ...)` provides a masked
  //!     version of `count_true which count the non masked non zero element
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/$name$.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(count_true_, count_true);
}

#include <eve/module/core/regular/impl/count_true.hpp>
