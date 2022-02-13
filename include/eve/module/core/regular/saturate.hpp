//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/clamp.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var saturate
  //!
  //! @brief Callable object computing the saturation of a value in a type.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | computation of the saturation of a value in a type         |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< real_value T, real_scalar_value Target>
  //!  auto operator()( T const& x, as_<Target> const& t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! ---
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value) to saturate.
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type to saturate `x` to.
  //!
  //! **Return value**
  //!
  //!For an  `x` of [real value](@ref eve::real_value) `Target`, the expression:
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!T  r = saturate(x, as_<Target>{});
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!is semantically equivalent to:
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!T vmin=static_cast<T>(Valmin<Target>());
  //!T vmax=static_cast<T>(Valmax<Target>());
  //!T r = convert(clamp(x,vmi,vmax),as(x));
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!@warning Note
  //!   Saturation operated by [eve::saturate](#eve::saturate) may lead to
  //!   Undefined Behaviors if it implies conversions that are themselves U.B.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::saturate
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `saturate[cond](x, ...)` is equivalent to `if_else(cond,saturate(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/saturate.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(saturate_, saturate);
}

#include <eve/module/core/regular/impl/saturate.hpp>
