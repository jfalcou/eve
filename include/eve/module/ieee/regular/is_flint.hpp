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
  //! @addtogroup predicates
  //! @{
  //! @var is_flint
  //!
  //! @brief Callable object computing the is_flint logical value.
  //!
  //! **Required header:** `#include <eve/function/is_flint.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the is_flint logical value              |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(floating_real_value auto x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!The call:
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!logical<T> r = is_flint(x);
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!is semantically  equivalent to: `eve::is_eqz(eve::frac(x))`;
  //!
  //!This means that x is a [floating real value](@ref eve::floating_real_value) representing an integer
  //!(flint is a shorcut for 'floating integer').
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::is_flint
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `is_flint[cond](x)` is equivalent to
  //! `if_else(cond,is_flint(x),false(as(is_flint(x))))`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!     Pedantically speaking flint stands for floating integer. The call `pedantic(is_flint)(x)` considers
  //!      that integral typed values are not floating and so `pedantic(is_flint)(x)` returns false for all elements of this types. Moreover a
  //!      floating point value is pedantically deemed as flint only is the next representable value is not flint, so
  //!      great floating values are not pedantically flint.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/is_flint.cpp}
  //!
  //!  @}
  //================================================================================================

  EVE_MAKE_CALLABLE(is_flint_, is_flint);
}

#include <eve/module/ieee/regular/impl/is_flint.hpp>
