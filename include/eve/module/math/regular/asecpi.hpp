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
  //! @addtogroup invtrigonometric
  //! @{
  //! @var asecpi
  //!
  //! @brief Callable object computing asecpi.
  //!
  //! **Required header:** `#include <eve/function/asecpi.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of asecpi   |
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
  //!Returns the [elementwise](@ref glossary_elementwise) arc secant of the
  //!input in \f$\pi\f$ mutiples in the range \f$[0, 1]\f$.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$1\f$, \f$+0\f$ is returned.
  //!   * If the element is \f$0\f$, \f$1\f$ is returned.
  //!   * If the element \f$|x| < 1\f$, `NaN` is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/asecpi.hpp>`
  //!  
  //!     The expression `diff(asecpi)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/asecpi.cpp}
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct asecpi_; }
  template<> struct supports_conditional<tag::asecpi_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(asecpi_, asecpi);
}

#include <eve/module/math/regular/impl/asecpi.hpp>
