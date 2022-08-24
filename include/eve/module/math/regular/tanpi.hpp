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
//! @var tanpi
//!
//! @brief Callable object computing the tangent from an input in \f$\pi\f$ multiples.
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
//!      T tanpi(T x) noexcept;                                 //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> tanpi(eve::complex<T> z) noexcept;     //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!   *  `z`:   [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   1. Returns the [elementwise](@ref glossary_elementwise) tangent of the input expressed in \f$\pi\f$
//!      multiples. In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, Nan is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the tangent of the input
//!      in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/math/tanpi.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/tanpi.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================

EVE_MAKE_CALLABLE(tanpi_, tanpi);
}

#include <eve/module/math/regular/impl/tanpi.hpp>
