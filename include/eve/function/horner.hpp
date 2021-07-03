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
  //! @var horner
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/horner.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the horner operation.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the horner operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T0, value... Ts>                                    auto operator()(T0 x, Ts... args) const noexcept;
  //!  template< value T0, range R>                                        auto operator()(T0 x, R r) const noexcept;
  //!  template< value T0, std::inputiterator IT, std::inputiterator IT>   auto operator()(T0 x, IT first, IT sentinel) const noexcept;
  //!  template< value T0, value... Ts>                                    auto operator()(T0 x, callable_one_ const & o, Ts... args) const noexcept;
  //!  template< value T0, range R>                                        auto operator()(T0 x, callable_one_ const & o, R r) const noexcept;
  //!  template< value T0, std::inputiterator IT, std::inputiterator IT>   auto operator()(T0 x, callable_one_ const & o, IT first, IT sentinel) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value x](../../concepts.html#value).
  //!`o`:   [callable_one_ ](../../concepts.html#value). Put eve::one here to have an unitary polynomial and a small optimization
  //!`args`:   [values ](../../concepts.html#value) expansion pack associated to \f$(a_i)_{i_0\le i \le n}\f$. \f$i_0\f$ is 1 if o is present else 0
  //!`r`:   [values ](../../concepts.html#value) Range containing the coefficients in the same conditions
  //!`first`, `sentinel`:   std::input_iterator conforming pair of iterators through the coefficients in the same conditions
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
  //!  Higher-order function generating a masked version of eve::horner
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `horner[cond](x, ...)` is equivalent to `if_else(cond,horner(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `pedantic`
  //!
  //!     **Required header:**  #include <eve/function/pedantic/horner.hpp>
  //! 
  //!  
  //!     The expression `pedantic(horner)(...)` computes the result using `pedantic(fma)(a,x,b)` for `a*x+b` instead of
  //!      `fma(a,x,b)`.
  //!  
  //!  * `numeric`
  //!
  //!     **Required header:**  #include <eve/function/numeric/horner.hpp>
  //! 
  //!  
  //!     The expression `numeric(horner)(...)` computes the result using `numeric(fma)(a,x,b)` for `a*x+b` instead of
  //!      `fma(a,x,b)`.
  //!  
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/horner.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(horner_, horner);
}

#include <eve/module/real/polynomial/function/regular/generic/horner.hpp>
