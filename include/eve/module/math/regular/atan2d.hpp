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
  //! @var atan2d
  //!
  //! @brief Callable object computing the atan2d operation.
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
  //!      template< eve::floating_value T, eve::floating_value U >
  //!      T atan2d(T x, U y) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [floating real values](@ref eve::value)
  //!
  //! **Return value**
  //!
  //!the arc tangent of \f$\frac{y}x\f$  in the range [-180 , +180] radians, is returned.
  //!The **IEEE** limiting values are almost all satisfied :
  //!
  //!     *  If `x` and `y` are both zero or infinites, Nan is returned (this is not standard conforming)
  //!     *  If `y` is \f$\pm0\f$ and `x` is strictly negative or \f$-0\f$, \f$\pm180\f$ is returned
  //!     *  If `y` is \f$\pm0\f$ and `x` is strictly positive or \f$+0\f$, \f$\pm0\f$ is returned
  //!     *  If `y` is \f$\pm\inft`y`\f$ and `x` is finite, \f$\pm90\f$ is returned
  //!     *  If `x` is \f$\pm0\f$ and `y` is strictly negative, \f$-90\f$ is returned
  //!     *  If `x` is \f$\pm0\f$ and `y` is strictly positive, \f$+90\f$  is returned
  //!     *  If `x` is \f$-\inft`y`\f$ and `y` is finite and positive, \f$+180\f$ is returned
  //!     *  If `x` is \f$-\inft`y`\f$ and `y` is finite and negative, \f$-180\f$ is returned
  //!     *  If `x` is \f$+\inft`y`\f$ and `y` is finite and positive, \f$+0\f$ is returned
  //!     *  If `x` is \f$+\inft`y`\f$ and `y` is finite and negative, \f$-0\f$ is returned
  //!     *  If either `x` is Nan or `y` is Nan, Nan is returned
  //!
  //!     The call will return a NaN if `x` and `y` are both either null or infinite: this result is not **IEEE** conform,
  //!     but not more absurd than the IEEE choices and allows to simplify (and speed) the implementation.
  //!     In all other cases, the result is standard conformant.
  //!
  //!The result type is the [common compatible type](@ref common_compatible) of the two parameters.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/atan2d.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!  * eve::pedantic
  //!
  //!     The call `pedantic(atan2d)(`x`,`y`)` returns the same results as the regular call, but all
  //!      **IEEE** limiting values are satisfied :
  //!
  //!       *  If `y` is \f$\pm\infty\f$ and `x` is \f$-\inft`y`\f$,\f$\pm135\f$ is returned
  //!       *  If `y` is \f$\pm\infty\f$ and `x` is \f$+\infty\f$, \f$\pm45\f$ is returned
  //!       *  If `x` is \f$\pm0\f$ and `y` is \f$\pm-0\f$, \f$-90\f$ is returned
  //!       *  If `x` is \f$\pm0\f$ and `y` is \f$\pm+0\f$, \f$+90\f$  is returned
  //!  @}
  //================================================================================================

  namespace tag { struct atan2d_; }
  template<> struct supports_conditional<tag::atan2d_> : std::false_type {};

  EVE_MAKE_CALLABLE(atan2d_, atan2d);
}

#include <eve/module/math/regular/impl/atan2d.hpp>
