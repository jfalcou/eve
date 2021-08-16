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
  //! @addtogroup special
  //! @{
  //! @var betainc_inv
  //!
  //! @brief Callable object computing the inverse relative to the first parameter
  //!        of the beta incomplete function.
  //!
  //! **Required header:** `#include <eve/function/betainc_inv.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the betainc_inv operation                                  |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_value T, floating_value U, floating_value V > auto operator()( T s, U x, V y ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Returns [element-wise](@ref glossary_elementwise) the value of the inverse of incomplete beta function
  //!relative to the first parameter.
  //!
  //! The result type is the [common compatible type](@ref common_compatible) of the two parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::betainc_inv
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `betainc_inv[cond](x, ...)` is equivalent to `if_else(cond,betainc_inv(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //! * eve::diff
  //!
  //!:   **Required header:** `#include <eve/function/diff/betainc_inv.hpp>`
  //!
  //!:   The expression `diff(betainc_inv)(s,x,y)` computes the partial
  //!    diff of \f$f\f$, where \f$f\f$ is the function \f$s \rightarrow \ \mbox{B}(s,x,y)\f$.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/betainc_inv.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(betainc_inv_, betainc_inv);
}

#include <eve/module/real/special/function/regular/generic/betainc_inv.hpp>
