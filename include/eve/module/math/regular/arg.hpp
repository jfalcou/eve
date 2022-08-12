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
  //! @addtogroup math_trig
  //! @{
  //! @var arg
  //!
  //! @brief Callable object computing the phase angle (in radians).
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
  //!      template< eve::floating_value T >
  //!      T arg(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!    `x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!   Returns the [elementwise](@ref glossary_elementwise)
  //!   the phase angle (in radians) of the input.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/arg.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::arg[mask](x)` provides a masked version of `eve::arg` which is
  //!     equivalent to `if_else (mask, abs(x), x)`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/math/masked/arg.cpp}
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(arg_, arg);
}

#include <eve/module/math/regular/impl/arg.hpp>
