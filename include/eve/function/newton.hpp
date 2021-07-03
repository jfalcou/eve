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
  //! @addtogroup polynomial
  //! @{
  //! @var newton
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/newton.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the newton operation.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the newton operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T0, range Rc,range Rn>                                auto operator()(T0 x, Rc coefs, Rn nodes) const noexcept;
  //!  template< value T0, std::inputiterator ITc, std::inputiterator ITn>   auto operator()(T0 x, ITc firstcoef, ITc sentinel,ITn firstnode) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value x](../../concepts.html#value).
  //!`coefs`, `nodes``:   [values ](../../concepts.html#value) Range containing the coefficients
  //!`firstcoef`, `sentinel`,`firstnode`:   std::input_iterator conforming pair of iterators through the coefficients and start of the nodes
  //!
  //!
  //!
  //! **Return value**
  //!
  //!Returns [element-wise](../../../glossary.html#value) the value of polynomial function(s)
  //!represented by the coefficients in decreasing power order at `x`.
  //!
  //!The result type is of the compatibility type of the  coefficients and the evaluation value `x`.
  //!
  //!@WARNING
  //!   If the coefficients are simd values of cardinal N, this means you compute the values of N polynomials.
  //!   If x is scalar, the polynomials are all computed at the same point, but
  //!   If x is simd, the nth polynomial is computed on the nth value of x.
  //!
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::newton
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `newton[cond](x, ...)` is equivalent to `if_else(cond,newton(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `pedantic`
  //!
  //!     **Required header:**  #include <eve/function/pedantic/newton.hpp>
  //! 
  //!  
  //!     The expression `pedantic(newton)(...)` computes the result using `pedantic(fma)(a,x,b)` for `a*x+b` instead of
  //!      `fma(a,x,b)`.
  //!  
  //!  * `numeric`
  //!
  //!     **Required header:**  #include <eve/function/numeric/newton.hpp>
  //! 
  //!  
  //!     The expression `numeric(newton)(...)` computes the result using `numeric(fma)(a,x,b)` for `a*x+b` instead of
  //!      `fma(a,x,b)`.
  //!  
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/newton.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(newton_, newton);
}

#include <eve/module/real/polynomial/function/regular/generic/newton.hpp>
