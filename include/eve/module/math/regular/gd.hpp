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
  //! @var gd
  //!
  //! @brief Callable object computing the gudermanian gd: \f$\int_0^\infty 1/\cosh x dx\f$.
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
  //!      T gd(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) gudermanian of the input.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, 0 is returned.
  //!   * If the element is \f$\pm\infty\f$, \f$\pm\pi/2\f$ is returned.
  //!   * If the element is a `NaN`, `NaN` is returned.
  //!
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!
  //!  Higher-order function generating a masked version of eve::gd
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `gd[cond](x)`
  //!  is equivalent to `if_else(cond,gd(x),x)`
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/gd.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(gd_, gd);
}

#include <eve/module/math/regular/impl/gd.hpp>
