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
  //! @var acosh
  //!
  //! @brief Callable object computing acosh;  \f$\log(x+\sqrt{x^2-1})\f$.
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
  //!      T acosh(T x) noexcept;
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
  //!For values in the domain `x>1`, the inverse hyperbolic cosine is semantically equivalent to \f$\log(x+\sqrt{x^2-1})\f$.
  //!
  //!In particular:
  //!
  //!   * If the element is less than \f$1\f$ or `Nan`, `NaN` is returned.
  //!   * If the element is \f$1\f$, \f$+0\f$ is returned.
  //!   * If the element is \f$+\infty\f$, \f$+\infty\f$ is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/acosh.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(acosh_, acosh);
}

#include <eve/module/math/regular/impl/acosh.hpp>
