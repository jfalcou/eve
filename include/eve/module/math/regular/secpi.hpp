//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup trigonometric
  //! @{
  //! @var secpi
  //!
  //! @brief Callable object computing secpi.
  //!
  //! **Required header:** `#include <eve/function/secpi.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of secpi   |
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
  //!Returns the [elementwise](@ref glossary_elementwise) secine of the input expressed in \f$\pi\f$ multiples.
  //!
  //!The call `secpi(x)` is semantically equivalent to \f$\sec(\pi x)\f$.
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$1\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, Nan is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::quarter_circle, eve::half_circle, eve::full_circle, 
  //!
  //!     provide a balance between speed and range limitation.
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/secpi.hpp>`
  //!
  //!     The expression `diff(secpi)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/secpi.cpp}
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct secpi_; }
  template<> struct supports_conditional<tag::secpi_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(secpi_, secpi);
}

#include <eve/module/math/regular/impl/secpi.hpp>
