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
  //! @addtogroup math
  //! @{
  //! @var atanpi
  //!
  //! @brief Callable object computing atand.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of atand   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(floating_value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) arc cotangent of the
  //!input in the range \f$[-\frac12, \frac12]\f$.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, \f$\pm\frac\pi2\f$ is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!
  //!     The expression `diff(atanpi)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/atanpi.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct atanpi_; }
  template<> struct supports_conditional<tag::atanpi_> : std::false_type {};

  EVE_MAKE_CALLABLE(atanpi_, atanpi);
}

#include <eve/module/math/regular/impl/atanpi.hpp>
