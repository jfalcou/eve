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
  //! @var acosd
  //!
  //! @brief Callable object computing acosd.
  //!
  //! **Required header:** `#include <eve/function/acosd.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of acosd   |
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
  //!Returns the [elementwise](@ref glossary_elementwise) value in degrees of the arc cosine of the
  //!input in the range \f$[0 , 180]\f$.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$1\f$, \f$+0\f$ is returned.
  //!   * If the element \f$|x| > 1\f$, `NaN` is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/acosd.hpp>`
  //!
  //!     The expression `diff(acosd)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/acosd.cpp}
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct acosd_; }
  template<> struct supports_conditional<tag::acosd_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(acosd_, acosd);
}

#include <eve/module/math/regular/impl/acosd.hpp>
