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
  //! @addtogroup core
  //! @{
  //! @var sum_of_prod
  //!
  //! @brief Callable object computing the sum_of_prod operation.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the sum_of_prod operation                                      |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U, value V, value W, value Ts...> auto operator()( T x, U y, V z, W t, Ts... args)
  //!  const noexcept requires compatible< T, U, V, W, Ts...>;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`, `z`, `t`, `args`:   [values](@ref eve::value). the total number of arguments must be even
  //!
  //! **Return value**
  //!
  //! computes [elementwise](@ref glossary_elementwise) accurately the sum of products of arguments (at lest 4):
  //!
  //! If the arguments are renamed (a_i)_{0 < \le i < \lt n} the object function computes \f$ \displaystyle \sum_0^{(n+1)/2} a_{2n}*a_{2n+1}\f$.
  //! but if the system is able to compute correct fma the result is more accurate than this naïve formula.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!
  //!     The call `pedantic(fma)(x,y,z,t...)` uses pedantic(fma). This can be very expensive if the
  //!      system has no hardware capability.
  //!  * eve::pedantic
  //!
  //!
  //!     The call `pedantic(fma)(x,y,z,t...)` uses pedantic(fma). This can be very expensive if the
  //!      system has no hardware capability.
  //!  * eve::numeric
  //!
  //!
  //!     The call `numeric(fma)(x,y,zt...)` uses numeric(fma). This can be very expensive if the
  //!      system has no hardware capability.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/sum_of_prod.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct sum_of_prod_; }
  template<> struct supports_conditional<tag::sum_of_prod_> : std::false_type {};

  EVE_MAKE_CALLABLE(sum_of_prod_, sum_of_prod);
}

#include <eve/module/core/regular/impl/sum_of_prod.hpp>
