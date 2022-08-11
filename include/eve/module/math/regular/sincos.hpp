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
  //! @var sincos
  //!
  //! @brief Callable object computing the simultaneous  computation of sin an cos.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the simultaneous  computation of sin an cos   |
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
  //!The computation returns a pair and is semantically equivalent to `{sin(x), cos(x)}`
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
  //! @godbolt{doc/math/sincos.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct sincos_; }
  template<> struct supports_conditional<tag::sincos_> : std::false_type {};

  EVE_MAKE_CALLABLE(sincos_, sincos);
}

#include <eve/module/math/regular/impl/sincos.hpp>
