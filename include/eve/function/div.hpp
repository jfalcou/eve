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
  //! @addtogroup operators
  //! @{
  //! @var div
  //!
  //! @brief Callable object performing the division of multiple values.
  //!
  //! **Required header:** `#include <eve/function/div.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the absolute value of its parameter               |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::value auto const& x, eve::value auto const&... xs) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //! `x`    Instance of eve::value.
  //!
  //! `xs`:  Instances of eve::value. Behavior is undefined if the expected result type is integral and any `xs` is  equal to 0.
  //!
  //! **Return value**
  //!
  //! A value of the [common compatible type](@ref common_compatible) of `x` and all `xs` containing the
  //! [elementwise](@ref glossary_elementwise) division of `x` by all `xs`.
  //! The result is semantically equivalent to `x/mul(xs...)`
  //!
  //! With two parameters, the call `div(x, y)` is equivalent to `x / y` if `x` or  `y` is an  [simd value](@ref eve::simd_value).
  //!
  //!@warning
  //!   Although the infix notation with `/` is supported, the `/` operator on
  //!   standard scalar types is the original one and so can lead to automatic promotion.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::div
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `div[cond](x0,xs...)` is equivalent
  //!  to `if_else(cond,div(x0,xs...),x0)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::saturated
  //!
  //!     **Required header:** `#include <eve/function/saturated/div.hpp>`
  //!
  //!     The expression `eve::saturated(eve::div)(x, xs...)` computes the saturated division of `x` by
  //!     all `xs`. The result is semantically equivalent to `x/saturated(mul)(xs...)` but is always defined even
  //!     if the denominator is 0.
  //!
  //!     The relevant cases are just in fact  the division by 0 for integral types in which case the result
  //!     is [`eve::Valmin(as(x))`](@ref eve::valmin) or
  //!     [`eve::Valmax(as(x))`](ref eve::valmax) according to the dividend sign, and
  //!     the division of [`eve::Valmin(as(x))`](@ref eve::valmin)
  //!     by -1 that produces [`eve::Valmax(as(x))`](@ref eve::valmax).
  //!
  //!   * `toward_zero`
  //!     The call `toward_zero(div)(x, y)`  computes  `trunc(div(x, y))`.
  //!
  //!   * `downward`
  //!     The call `downward(div)(x, y)`  computes  `floor(div(x, y))`.
  //!
  //!   * `upward`
  //!     The call `upward(div)(x, y)`  computes  `ceil(div(x, y))`.
  //!
  //!   * `to_nearest`
  //!     The call `to_nearest(div)(x, y)`  computes  `nearest(div(x,y))`.
  //!
  //!   * eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/div.hpp>`
  //!
  //!     The expression `eve::diff_nth<N>(eve::div)(x, xs...)` computes the derivative of the division
  //!     over the Nth parameter.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/div.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(div_, div);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/div.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/div.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/div.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/div.hpp>
#endif
