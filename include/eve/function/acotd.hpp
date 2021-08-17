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
  //! @var acotd
  //!
  //! @brief Callable object computing acotd.
  //!
  //! **Required header:** `#include <eve/function/acotd.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of acotd   |
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
  //!input in the range \f$]-90, 90]\f$.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$\pm90\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/acotd.hpp>`
  //!  
  //!     The expression `diff(acotd)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/acotd.cpp}
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct acotd_; }
  template<> struct supports_conditional<tag::acotd_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(acotd_, acotd);
}

#include <eve/module/real/math/function/regular/generic/acotd.hpp>
