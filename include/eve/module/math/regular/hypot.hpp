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
  //! @addtogroup math_exp
  //! @{
  //! @var hypot
  //!
  //! @brief Callable object computing the \f$l_2\f$ norm of its inputs.
  //!
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
  //!      template< floating_value P, floating_value T, floating_value ... Ts>
  //!      auto hypot( T x,Ts ... args ) const noexcept
  //!   }
  //!   @endcode
  //!
  //!
  //! **Parameters**
  //!
  //!   `p`, `x`, `... args`:   [floating values](@ref eve::floating_value)
  //!
  //! **Return value**
  //!
  //!   *  \f$\sqrt{\sum_1^n |x_i|^2}\f$ is returned
  //!
  //!   *  The result type is the [common compatible type](@ref common_compatible) of the parameters.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/hypot.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::hypot[mask](x, ...)` provides a masked version of `eve::hypot` which is
  //!     equivalent to `if_else (mask, hypot(x, ...), x)`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/math/masked/hypot.cpp}
  //!
  //!    * eve::pedantic
  //!
  //!      The call `pedantic(hypot)(x,args...)`  computes the square root of the sum of
  //!      the squares of the parameters
  //!      without undue overflow or underflow at intermediate stages of the computation
  //!      and can be more accurate than the non-decorated call.
  //!
  //!      Morever it returns \f$\infty\f$ as soon as one of its parameter is infinite,
  //!      regardless of possible `Nan` values.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/math/pedantic/hypot.cpp}
  //!  @}
  //================================================================================================

  EVE_MAKE_CALLABLE(hypot_, hypot);
}

#include <eve/module/math/regular/impl/hypot.hpp>
