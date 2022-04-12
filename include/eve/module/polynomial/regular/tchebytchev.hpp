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
  //! @addtogroup polynomial
  //! @{
  //! @var tchebytchev
  //!
  //! @brief Callable object computing the tchebytchev polynomial of degree n at x.
  //!
  //! **Required header:** `#include <eve/module/polynomial.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the tchebytchev operation   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!   auto operator()( integral_real_value auto n, floating_value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [integral real valuex](@ref eve::integral_real_value) or integral constant.
  //!
  //!`x`:   [floating valuex](@ref eve::floating_value).
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) the value of the  tchebytchev polynomial of
  //!first kind and order `n` at `x` \f$T_n(x)\f$:
  //!
  //!The result type is of the [common compatible type](@ref common_compatible) of the  parameters.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     The expression `diff(tchebytchev)(n,x)` computes the derivative of the function relative to `x`.
  //!
  //! #### alias
  //!
  //!     To desambiguate from tchebytchev polynomial of the second kind (tchebytchev_u) you can use tchebytchev_t
  //!     in place of tchebytchev
  //!
  //! #### Example
  //!
  //! @godbolt{doc/polynomial/tchebytchev.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(tchebytchev_, tchebytchev);
//  EVE_ALIAS_CALLABLE(chebytchev_t_, tchebytchev);
}

#include <eve/module/polynomial/regular/impl/tchebytchev.hpp>
