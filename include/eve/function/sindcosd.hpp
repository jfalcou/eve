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
  //! @var sindcosd
  //!
  //! @brief Callable object computing the simultaneous  computation of sin an cos of an argument in degrees.
  //!
  //! **Required header:** `#include <eve/function/sindcosd.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the simultaneous  computation of sin an cos of an argument in degrees   |
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
  //!The computation returns a pair and is semantically equivalent to `{sind(x), cosd(x)}`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::restricted, eve::small, eve::medium, eve::big
  //!
  //!     provide a balance between speed and range limitation.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/sindcosd.cpp}
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct sindcosd_; }
  template<> struct supports_conditional<tag::sindcosd_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(sindcosd_, sindcosd);
}

#include <eve/module/real/math/function/regular/generic/sindcosd.hpp>
