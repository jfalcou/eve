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
  //! @var sinhc
  //!
  //! @brief Callable object computing sinhc: \f$\frac{e^x-e^{-x}}{2x}\f$.
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
  //!      T sinhc(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating value](@ref eve::floating_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) hyperbolic sine of the input divided by the input.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$1\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, \f$\pm\infty\f$ is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!
  //!  Higher-order function generating a masked version of eve::sinhc
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `sinhc[cond](x, ...)` is equivalent to `if_else(cond,sinhc(x, ...),x)`
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/sinhc.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sinhc_, sinhc);
}

#include <eve/module/math/regular/impl/sinhc.hpp>
