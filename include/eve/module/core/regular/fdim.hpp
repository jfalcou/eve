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
  //! @addtogroup core_arithmetic
  //! @{
  //!   @var fmod
  //!   @brief Computes the fmodolute value of the parameter.
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
  //!      template< eve::value T, eve::value U >
  //!      T fmod(T x, U y) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y` :  arguments.
  //!
  //!   **Return value**
  //!
  //!       Returns the  [elementwise](@ref glossary_elementwise) positive difference between `x` and `y`:
  //!          * if `x>y`,   x-y is returned
  //!          * if `x<=y`,  +0 is returned
  //!          * otherwise a `Nan` is returned
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/fmod.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve;::fmod[mask](x)` provides a masked version of `eve::fmod` which is
  //!     equivalent to `if_else (mask, fmod(x), x)`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/fmod.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(fdim_, fdim);
}

#include <eve/module/core/regular/impl/fdim.hpp>
