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
  //! @addtogroup math_exp
  //! @{
  //! @var exp
  //!
  //! @brief Callable object computing \f$e^x\f$.
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
  //!      T exp(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating value](@ref eve::floating_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) exponential of the input.
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$1\f$ is returned
  //!   * If the element is \f$-\infty\f$, \f$+0\f$ is returned
  //!   * If the element is \f$\infty\f$, \f$\infty\f$ is returned
  //!   * If the element is a `NaN`, `NaN` is returned
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/exp.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve;::exp[mask](x)` provides a masked version of `eve::exp` which is
  //!     equivalent to `if_else (mask, exp(x), x)`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/math/masked/exp.cpp}
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(exp_, exp);
}

#include <eve/module/math/regular/impl/exp.hpp>
