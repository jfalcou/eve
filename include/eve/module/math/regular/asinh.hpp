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
  //! @var asinh
  //!
  //! @brief Callable object computing asinh: \f$\log(x+\sqrt{x^2+1})\f$.
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
  //!      T asinh(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cosine of the input.
  //!The inverse hyperbolic sine is semantically equivalent to \f$\log(x+\sqrt{x^2+1})\f$.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, \f$\pm\infty\f$ returned.
  //!   * If the element is a `NaN`, `NaN` is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/asinh.cpp}
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(asinh_, asinh);
}

#include <eve/module/math/regular/impl/asinh.hpp>
