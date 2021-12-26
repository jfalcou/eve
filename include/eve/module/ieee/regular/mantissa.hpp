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
  //! @var mantissa
  //!
  //! @brief Callable object computing the mantissa value.
  //!
  //! **Required header:** `#include <eve/function/mantissa.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the mantissa value   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(floating_value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating_real_value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!    Computes the [elementwise](@ref glossary_elementwise) ieee mantissa of the floating value.
  //!
  //!    The mantissa \f$e\f$ and mantissa \f$m\f$ of a floating point entry \f$x\f$ are related by
  //!    \f$x =  m\times 2^e\f$, with  \f$|m| \in [1, 2[\f$ (except for \f$x = \pm0, \pm\infty\f$ or is a Nan,
  //!    where \f$m=x\f$ and \f$e=0\f$).
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::mantissa
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `mantissa[cond](x, ...)` is equivalent to `if_else(cond,mantissa(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/ieee/mantissa.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(mantissa_, mantissa);
}

#include <eve/module/ieee/regular/impl/mantissa.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/ieee/regular/impl/simd/x86/mantissa.hpp>
#endif
