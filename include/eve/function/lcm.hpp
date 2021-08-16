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
  //! @addtogroup combinatorial
  //! @{
  //! @var lcm
  //!
  //! @brief Callable object computing least common multiple.
  //!
  //! **Required header:** `#include <eve/function/lcm.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | least common multiple operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T p, U n ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`p`, `n`:   [real values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //! The result type is the [common compatible type](@ref common_compatible) of the two parameters.
  //!
  //!@warning
  //!    `p` and `n` can be of any [real values](@ref eve::value) type, but when the types are not integral
  //!    the least common multiple is defined only if `p` and `n` element are flint. If it is not the
  //!    case the corresponding result will be Nan.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::lcm
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `lcm[cond](x, ...)` is equivalent to `if_else(cond,lcm(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!If the user calls the function with floating parameters, he can enforce the fact that all parameters are flint
  //!using one of the  [roundings](./../decorator.html#roundings) decorators on the object function. Namely:
  //!
  //!   - deco(lcm)(a,b) is equivalent to lcm)(deco(round)(a),deco(round)(b)), but optimized when possible.
  //!
  //!where deco is one of: `to_nearest`, `downward`, `upward` or `toward_zero`.
  //!
  //! ---
  //!
  //! #### Type conversion
  //!
  //!If the input types are integral, the result is succeptible to overflow, but will never be greater than the product of the two
  //!input values which will be representable in the upgraded integral type:
  //!
  //!The call `upgrade(lcm)(a,b)` will then return a correct result in the upgraded type (see example below).
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/lcm.cpp
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct lcm_; }

  template<>
  struct supports_optimized_conversion<tag::lcm_> : std::true_type {};

  EVE_MAKE_CALLABLE(lcm_, lcm);
}

#include <eve/module/real/combinatorial/function/regular/generic/lcm.hpp>
