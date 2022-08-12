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
  //! @var nthroot
  //!
  //! @brief Callable object computing the nth root: \f$x^{1/n}\f$.
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
  //!      template< eve::floating_value T, eve::floating_value U >
  //!      T nthroot(T x, U y) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!   * `x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //!   * `n`:   [integral_value](@ref eve::integral_value). Actually `n` can be a [flint](@ref eve::is_flint).
  //!
  //! **Return value**
  //!
  //!    *  Returns [elementwise](@ref glossary_elementwise) the value of \f$x^{1/n}\f$.
  //!       For negative `x` the value returned is a Nan as soon as `n` is not an odd integer.
  //!
  //!    *  The result type is of the compatibility type of the  parameters.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/nthroot.cpp}
  //!
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::nthroot[mask](x, n)` provides a masked version of `eve::nthroot` which is
  //!     equivalent to `if_else (mask, nthroot(x, n), x)`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/math/masked/nthroot.cpp}
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(nthroot_, nthroot);
}

#include <eve/module/math/regular/impl/nthroot.hpp>
