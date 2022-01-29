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
  //! @addtogroup ieee754
  //! @{
  //! @var bitofsign
  //!
  //! @brief Callable object computing the bitofsign value.
  //!
  //! **Required header:** `#include <eve/function/bitofsign.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the bitofsign value   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!The call `bitofsign(x)` is semantically equivalent to `x & signmask(as(x))`.
  //!
  //!@warning
  //!   Take care that for  [floating real values](@ref eve::value) bitofsign does NOT return
  //!   a [logical value](@ref eve::value) that can be tested, but `mzero(as(x))` if `x` is negative
  //!   and  `zero(as(x))` if `x` is positive, which both satisfy the `x == 0` predicate.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::bitofsign
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `bitofsign[cond](x, ...)` is equivalent to `if_else(cond,bitofsign(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/bitofsign.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(bitofsign_, bitofsign);
}

#include <eve/module/core/regular/impl/bitofsign.hpp>
