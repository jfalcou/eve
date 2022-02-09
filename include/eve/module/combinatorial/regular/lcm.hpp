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
  //! @addtogroup combinatorial
  //! @{
  //! @var lcm
  //!
  //! @brief Callable object computing least common multiple.
  //!
  //! **Required header:** #include <eve/module/combinatorial.hpp>
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
  //!    the least common multiple is defined only if `p` and `n` element are [flint](@ref eve::is_flint). If any
  //!    of the arguments is not flint the result is undefined.
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
  //! #### Type conversion
  //!
  //!If the input types are integral, the result is succeptible to overflow, but will never be greater than the product of the two
  //!input values which will be representable in the upgraded integral type:
  //!
  //!The call `upgrade(lcm)(a,b)` will then return a correct result in the upgraded type (see example below).
  //!
  //! #### Example
  //!
  //! @godbolt{doc/combinatorial/lcm.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct lcm_; }

  template<>
  struct supports_optimized_conversion<tag::lcm_> : std::true_type {};

  EVE_MAKE_CALLABLE(lcm_, lcm);
}

#include <eve/module/combinatorial/regular/impl/lcm.hpp>
