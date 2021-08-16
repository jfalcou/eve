//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup invtrigonometric
  //! @{
  //! @var atan2pi
  //!
  //! @brief Callable object computing the atan2pi operation.
  //!
  //! **Required header:** `#include <eve/function/atan2pi.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the atan2pi operation   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y ) const noexcept
  //!  requires compatible< T,U>;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [floating real values](@ref eve::value)
  //!
  //! **Return value**
  //!
  //!the arc tangent of \f$\frac{y}x\f$  in the range [-1, +1] radians, is returned.
  //!The **IEEE** limiting values are almost all satisfied :
  //!
  //!     -  If `x` and `y` are both zero or infinites, Nan is returned (this is not standard conforming)
  //!     -  If `y` is \f$\pm0\f$ and `x` is strictly negative or \f$-0\f$, \f$\pm1\f$ is returned
  //!     -  If `y` is \f$\pm0\f$ and `x` is strictly positive or \f$+0\f$, \f$\pm0\f$ is returned
  //!     -  If `y` is \f$\pm\inft`y`\f$ and `x` is finite, \f$\pm\frac12\f$ is returned
  //!     -  If `x` is \f$\pm0\f$ and `y` is strictly negative, \f$-\frac12\f$ is returned
  //!     -  If `x` is \f$\pm0\f$ and `y` is strictly positive, \f$+\frac12\f$  is returned
  //!     -  If `x` is \f$-\inft`y`\f$ and `y` is finite and positive, \f$+1\f$ is returned
  //!     -  If `x` is \f$-\inft`y`\f$ and `y` is finite and negative, \f$-1\f$ is returned
  //!     -  If `x` is \f$+\inft`y`\f$ and `y` is finite and positive, \f$+0\f$ is returned
  //!     -  If `x` is \f$+\inft`y`\f$ and `y` is finite and negative, \f$-0\f$ is returned
  //!     -  If either `x` is Nan or `y` is Nan, Nan is returned
  //!
  //!     The call will return a NaN if `x` and `y` are both either null or infinite: this result is not **IEEE** conform,
  //!     but not more absurd than the IEEE choices and allows to simplify (and speed) the implementation.
  //!     In all other cases, the result is standard conformant.
  //!
  //!The result type is the [common compatible type](@ref common_compatible) of the two parameters.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/atan2pi.hpp>`
  //!
  //!     The call `pedantic(atan2pi)(`x`,`y`)` returns the same results as the regular call, but all
  //!      **IEEE** limiting values are satisfied :
  //!
  //!       -  If `y` is \f$\pm\infty\f$ and `x` is \f$-\infty\f$, \f$\pm\frac34\f$ is returned
  //!       -  If `y` is \f$\pm\infty\f$ and `x` is \f$+\infty\f$, \f$\pm\frac14\f$ is returned
  //!       -  If `x` is \f$\pm0\f$ and `y` is \f$\pm-0\f$, \f$-\frac12\f$ is returned
  //!       -  If `x` is \f$\pm0\f$ and `y` is \f$\pm+0\f$, \f$+\frac12\f$  is returned
  //!
  //!  * eve::diff_1st, eve::diff_2nd
  //!
  //!     **Required header:** `#include <eve/function/diff/atan2pi.hpp>`
  //!
  //!     The expression `diff_1st(atan2pi)(x,y)` and `diff_2nd(atan2pi)(x,y)` computes the partial
  //!      derivatives of \f$f\f$, where \f$f\f$ is the function \f$(x,y) \rightarrow \ \mbox{atan2pi}(x,y)\f$.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/atan2pi.cpp
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct atan2pi_; }
  template<> struct supports_conditional<tag::atan2pi_> : std::false_type {};

  EVE_MAKE_CALLABLE(atan2pi_, atan2pi);
}

#include <eve/module/real/math/function/regular/generic/atan2pi.hpp>
