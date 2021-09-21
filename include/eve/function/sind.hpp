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
  //! @var sind
  //!
  //! @brief Callable object computing sind.
  //!
  //! **Required header:** `#include <eve/function/sind.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of sind                                   |
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
  //!Returns the [elementwise](@ref glossary_elementwise) sine of the input expressed in degrees.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$1\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, Nan is returned.
  //!   * If the element is a `NaN`, `NaN` is returned.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::restricted, eve::small, eve::medium, eve::big
  //!
  //!     provide a balance between speed and range limitation.
  //!  
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/sind.hpp>`
  //!  
  //!     The expression `diff(sind)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/sind.cpp}
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct sind_; }
  template<> struct supports_conditional<tag::sind_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(sind_, sind);
}

#include <eve/module/real/math/function/regular/generic/sind.hpp>
