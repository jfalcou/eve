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
  //! @var quadrant
  //!
  //! @brief Callable object computing the quadrant value.
  //!
  //! **Required header:** #include <eve/module/math.hpp>
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the quadrant value   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [real_value](@ref eve::real_value).
  //!
  //! **Return value**
  //!
  //!return a value of the same type as `x` containing the quadrant number where `x` (supposed an integer) lies.
  //!
  //!@warning
  //!   the input `x` must be an integral or a [flint](@ref eve::is_flint) value.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/quadrant.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct quadrant_; }
  template<> struct supports_conditional<tag::quadrant_> : std::false_type {};

  EVE_MAKE_CALLABLE(quadrant_, quadrant);
}

#include <eve/module/math/regular/impl/quadrant.hpp>
