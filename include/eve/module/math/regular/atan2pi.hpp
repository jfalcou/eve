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
//! @var atan2pi
//!
//! @brief Callable object computing  the arc tangent in \f$\pi\f$ multiples using the
//! signs of arguments to determine the correct quadrant.
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
//!      T atan2pi(T x) noexcept;
//!   }
//!   @endcode
//!
//!  requires compatible< T,U>;
//!
//! **Parameters**
//!
//!`x`, `y`:   [floating real values](@ref eve::value)
//!
//! **Return value**
//!
//! the arc tangent of \f$\frac{y}x\f$  in the range [-1, +1] radians, is returned.
//! The **IEEE** limiting values are almost all satisfied :
//!
//!   *  If `x` and `y` are both zero or infinites, Nan is returned (this is not standard
//!      conforming)
//!   *  If `y` is \f$\pm0\f$ and `x` is strictly negative or \f$-0\f$, \f$\pm1\f$ is returned
//!   *  If `y` is \f$\pm0\f$ and `x` is strictly positive or \f$+0\f$, \f$\pm0\f$ is returned
//!   *  If `y` is \f$\pm\infty\f$ and `x` is finite, \f$\pm\frac12\f$ is returned
//!   *  If `x` is \f$\pm0\f$ and `y` is strictly negative, \f$-\frac12\f$ is returned
//!   *  If `x` is \f$\pm0\f$ and `y` is strictly positive, \f$+\frac12\f$  is returned
//!   *  If `x` is \f$-\infty\f$ and `y` is finite and positive, \f$+1\f$ is returned
//!   *  If `x` is \f$-\infty\f$ and `y` is finite and negative, \f$-1\f$ is returned
//!   *  If `x` is \f$+\infty\f$ and `y` is finite and positive, \f$+0\f$ is returned
//!   *  If `x` is \f$+\infty\f$ and `y` is finite and negative, \f$-0\f$ is returned
//!   *  If either `x` is Nan or `y` is Nan, Nan is returned
//!
//!   The call will return a NaN if `x` and `y` are both either null or infinite: this result is
//!   not **IEEE** conformant, but  allows to simplify (and
//!   speed) the implementation. In all other cases, the result is standard conformant.
//!
//!   The result type is the [common compatible type](@ref common_compatible) of the two parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/atan2pi.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!
//!  * eve::pedantic
//!
//!     The call `pedantic(atan2pi)(`x`,`y`)` returns the same results as the regular call, but all
//!      **IEEE** limiting values are satisfied :
//!
//!       *  If `y` is \f$\pm\infty\f$ and `x` is \f$-\infty\f$, \f$\pm\frac34\f$ is returned
//!       *  If `y` is \f$\pm\infty\f$ and `x` is \f$+\infty\f$, \f$\pm\frac14\f$ is returned
//!       *  If `x` is \f$\pm0\f$ and `y` is \f$\pm-0\f$, \f$-\frac12\f$ is returned
//!       *  If `x` is \f$\pm0\f$ and `y` is \f$\pm+0\f$, \f$+\frac12\f$  is returned
//!  @}
//================================================================================================

namespace tag
{
  struct atan2pi_;
}
template<> struct supports_conditional<tag::atan2pi_> : std::false_type
{};

EVE_MAKE_CALLABLE(atan2pi_, atan2pi);
}

#include <eve/module/math/regular/impl/atan2pi.hpp>
