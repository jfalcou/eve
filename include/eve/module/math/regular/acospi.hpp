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
//! @addtogroup math_invtrig
//! @{
//! @var acospi
//!
//! @brief Callable object computing the arc cosine in \f$\pi\f$ multiples.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      T acospi(T x) noexcept;                                   //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> acospi(eve::complex<T> z) noexcept;      //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!   *  `z`:   [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   1. Returns the [elementwise](@ref glossary_elementwise) arc cosine of the
//!      input in \f$\pi\f$ multiples, in the range \f$[0 , 1]\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$1\f$, \f$+0\f$ is returned.
//!      * If the element \f$|x| > 1\f$, `NaN` is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the complex principal value
//!      of the arc cosine of the input in \f$\pi\f$ multiples.
//!      Branch cuts exist outside the interval \f$[-1, +1]\f$ along the real axis.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/acospi.cpp}
//!
//!  @}
//================================================================================================

EVE_MAKE_CALLABLE(acospi_, acospi);
}

#include <eve/module/math/regular/impl/acospi.hpp>
