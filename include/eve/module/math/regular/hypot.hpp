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
//!      template< value T, value ... Ts>
//!      auto hypot( T x,Ts ... args ) const noexcept
//!   }
//!   @endcode
//!
//!
//! **Parameters**
//!
//!   `x`, `... args`:   [floating real or complex values](@ref eve::floating_value)
//!
//! **Return value**
//!
//!   \f$\sqrt{\sum_1^n |x_i|^2}\f$ is returned.
//!   The result type is the [common value type](@ref common_value_t) of the
//!   absolute values of the parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/hypot.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!    * eve::pedantic
//!
//!      The call `pedantic(hypot)(x,args...)`  computes the square root of the sum of
//!      the absolute squares of the parameters
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
