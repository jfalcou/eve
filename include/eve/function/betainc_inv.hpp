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
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/betainc_inv.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the betainc_inv operation.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the betainc_inv operation   |
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
  //!`x`, `y`:   [values](../../concepts.html#value).
  //!
  //!
  //!
  //! **Return value**
  //!
  //!Returns [element-wise](../../../glossary.html#value) the value of the incomplete beta function.
  //!
  //! The result type is the [compatibility result](../../concept.html#compatibility) of the two parameters.
  //!
  //![`diff`](../decorators.html#diff)
  //!:   **Required header: **<script type="preformatted">` #include <eve/function/diff/betainc_inv.hpp>`</script>
  //!
  //!:   The expression `diff(betainc_inv)(s,x,y)` computes the partial
  //!    diff of $f$, where $f$ is the function $s \rightarrow \ \mbox{B}(s,x,y)$.
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
  //!  decorators NOT FOUND
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
