//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math_exp
  //! @{
  //! @var expx2
  //!
  //! @brief Callable object computing \f$e^{\pm x^2}\f$.
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/math.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::floating_value T, eve::floating_value U >
  //!      T expx2(T x, U s) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!    `x`:   [floating value](@ref eve::floating_value).
  //!
  //! **Return value**
  //!
  //!     Returns the [elementwise](@ref glossary_elementwise) exponential of the square of `x`
  //!     multiplied by the sign of `s` trying to avoid overflow as possible.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/expx2.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve;::expx2[mask](x, ...)` provides a masked version of `eve::expx2` which is
  //!     equivalent to `if_else (mask, expx2(x, ...), x)`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/math/masked/expx2.cpp}
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(expx2_, expx2);
}

#include <eve/module/math/regular/impl/expx2.hpp>
