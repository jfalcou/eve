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
  //! @addtogroup math_hyper
  //! @{
  //! @var cosh
  //!
  //! @brief Callable object computing cosh: \f$\frac{e^x+e^{-x}}2\f$.
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
  //!      T cosh(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) hyperbolic cosine of the input.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, 1 is returned.
  //!   * If the element is \f$\pm\infty\f$, \f$+\infty\f$ is returned.
  //!   * If the element is a `NaN`, `NaN` is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/cosh.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cosh_, cosh);
}

#include <eve/module/math/regular/impl/cosh.hpp>
