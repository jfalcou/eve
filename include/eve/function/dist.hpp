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
  //! @addtogroup arithmetic
  //! @{
  //! @var dist
  //!
  //! @brief Callable object computing the distance between two values.
  //!
  //! **Required header:** `#include <eve/function/dist.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the distance operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](@ref eve::value)
  //!
  //! **Return value**
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!auto r = dist(x,y);
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!is semantically equivalent to:
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!auto r = abs(x-y);
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!   If an  [element](@ref glossary_element) of the expected result is not representable in
  //!   the result type, the corresponding result [element](@ref glossary_element) is undefined.
  //!
  //!   The result type is the [common compatible type](@ref common_compatible) of the two parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::dist
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `dist[cond](x, ...)` is equivalent to `if_else(cond,dist(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `saturated`
  //!
  //!     **Required header:** `#include <eve/function/saturated/dist.hpp>`
  //!
  //!     The call `saturated(dist)(x, y)` computes a saturated distance. Contrary to the non decorated case, it guarantees
  //!      that the result is always defined. If \f$|x-y|\f$ is not representable
  //!      [the greatest representable positive value](@ref eve::valmax) is returned
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/dist.hpp>`
  //!
  //!     The expression `diff_1st(dist)(x,y)` and `diff_2nd(dist)(x,y)` compute the partial
  //!      derivatives of \f$f\f$, where \f$f\f$ is the function \f$(x,y) \rightarrow \ |x-y|\f$.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/dist.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(dist_, dist);
}

#include <eve/module/real/core/function/regular/generic/dist.hpp>
