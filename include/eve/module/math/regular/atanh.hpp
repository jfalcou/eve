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
  //! @addtogroup math_invhyper
  //! @{
  //! @var atanh
  //!
  //! @brief Callable object computing atanh: \f$\frac{1}{2}\log((1+x)/(1-x))\f$.
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
  //!      T atanh(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cotangent of the input.
  //!The inverse hyperbolic sine is semantically equivalent to \f$\frac{1}{2}\log((1+x)/(1-x))\f$.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm1\f$, \f$\pm\infty\f$ is returned.
  //!   * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
  //!   * If the element is greater than one or a `NaN`, `NaN` is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/atanh.cpp}
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(atanh_, atanh);
}

#include <eve/module/math/regular/impl/atanh.hpp>
