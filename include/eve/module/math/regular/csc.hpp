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
//! @var csc
//!
//! @brief Callable object computing the cosecant of the input.
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
//!      T csc(T x) noexcept;                              //1
//!
//!      template< eve::floating_value T >
//!      as_complex_t<T> csc(as_complex_t<T> z) noexcept;  //2
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
//!   1.  Returns the [elementwise](@ref glossary_elementwise) cosecant of the input.
//!       (the inverse of the sine)
//!
//!       In particular:
//!
//!       * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!       * If the element is \f$\pm\infty\f$, Nan is returned.
//!       * If the element is a `NaN`, `NaN` is returned.
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the cosecant of the input
//!      i.e. \f$\1/sin(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/csc.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================

EVE_MAKE_CALLABLE(csc_, csc);
}

#include <eve/module/math/regular/impl/csc.hpp>
