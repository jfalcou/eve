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
  //! @var sinpicospi
  //!
  //! @brief Callable object computing the simultaneous  computation of sin an cos of an argument in .
  //!
  //! **Required header:** `#include <eve/function/sinpicospi.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the simultaneous  computation of sin an cos of an argument in    |
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
  //!The computation returns a pair and is semantically equivalent to `{sinpi(x), cospi(x)}`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::quarter_circle, eve::half_circle, eve::full_circle, 
  //!
  //!     provide a balance between speed and range limitation.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/sinpicospi.cpp}
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct sinpicospi_; }
  template<> struct supports_conditional<tag::sinpicospi_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(sinpicospi_, sinpicospi);
}

#include <eve/module/math/regular/impl/sinpicospi.hpp>
