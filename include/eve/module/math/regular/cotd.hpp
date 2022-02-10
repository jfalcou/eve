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
  //! @var cotd
  //!
  //! @brief Callable object computing cotd.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of cotd   |
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
  //!Returns the [elementwise](@ref glossary_elementwise) cotangent of the input expressed in degrees.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, Nan is returned.
  //!   * If the element is a `NaN`, `NaN` is returned.
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
  //!  
  //!     The expression `diff(cotd)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/cotd.cpp}
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct cotd_; }
  template<> struct supports_conditional<tag::cotd_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(cotd_, cotd);
}

#include <eve/module/math/regular/impl/cotd.hpp>
