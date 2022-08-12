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
  //! @var invgd
  //!
  //! @brief Callable object computing the inverse gudermanian.
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
  //!      T invgd(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //! Returns the [elementwise](@ref glossary_elementwise) inverse
  //! [gudermanian](@ref eve::gd) of the input.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, 0 is returned.
  //!   * If the element is \f$\pm\pi/2\f$, \f$\infty\f$ is returned.
  //!   * If the element is not in a  \f$[-\pi/2, \pi/2] \f$, `NaN` is returned.
  //!
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!
  //!  Higher-order function generating a masked version of eve::invgd
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `invgd[cond](x)` is equivalent to
  //! `if_else(cond,invgd(x),x)`
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/invgd.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(invgd_, invgd);
}

#include <eve/module/math/regular/impl/invgd.hpp>
