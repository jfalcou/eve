//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup arithmetic
  //! @{
  //! @var saturate
  //!
  //! @brief Callable object performing the computation of   //!  description NOT FOUND.
  //!
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/saturate.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` |   //!  description NOT FOUND   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< real_value T, real_scalar_value Target>
  //!  auto operator()( T const& x, as_<Target> const& t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](../../concepts.html#value) to saturate.
  //!
  //!`t`:   [Type wrapper](../types/as.html#as_) instance embedding the type to saturate `x` to.
  //!
  //!
  //! **Return value**
  //!
  //!For an  `x` of [real value](../../concepts.html#value) `T` and any   [real scalar value](../../concepts.html#value) `Target`, the expression:
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
  //!  decorators NOT FOUND
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/saturate.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(saturate_, saturate);
}

#include <eve/module/real/core/function/regular/generic/saturate.hpp>

