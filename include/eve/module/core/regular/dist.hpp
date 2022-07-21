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
  //! @disttogroup core_arithmetic
  //! @{
  //!   @var dist
  //!   @brief Computes the distance of its arguments.
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T, eve::value U >
  //!      eve::common_compatible_t<T, U> dist(T x, U y) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y` :  [arguments](eve::value).
  //!
  //!    **Return value**
  //!
  //!    The value of the distance of the arguments is returned,  i.e. `eve::abs (x-y)`.
  //!

  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/dist.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * eve::saturated
  //!
  //!     The call `saturated(dist)(x, y)` computes a saturated distance.
  //!     Contrary to the non decorated case, it guarantees
  //!     that the result is always defined. If \f$|x-y|\f$ is not representable
  //!     [the greatest representable positive value](@ref eve::valmax) is returned.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/saturated/dist.cpp}
  //! @}
  //================================================================================================

  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var dist
  //!
  //! @brief Callable object computing the distance between two values.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
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
  //!   If an  [element](@ref glossary_elementwise) of the expected result is not representable in
  //!   the result type, the corresponding result [element](@ref glossary_elementwise) is undefined.
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
  //!
  //!     The call `saturated(dist)(x, y)` computes a saturated distance. Contrary to the non decorated case, it guarantees
  //!      that the result is always defined. If \f$|x-y|\f$ is not representable
  //!      [the greatest representable positive value](@ref eve::valmax) is returned
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_nth
  //!
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

#include <eve/module/core/regular/impl/dist.hpp>
