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
  //! @brief Callable object evaluating the tchebytchev polynomial of degree n at x.
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
  //!  * eve::kind_1, kind_2
  //!
  //!     The expression `kind_1(tchebytchev)(n,x)` is identical to `tchebytchev(n,x)`.
  //!     The expression `kind_2(tchebytchev)(n,x)` evaluates the nth polynominial of tchebytchev of second kind \f$U_n\f$ at `x`.
  //!
  //!  * eve::successor
  //!
  //!     The expression `successor(tchebytchev)( x, yn, ynm1)` computes the value of \f$T_{n+1}(x)\f$ (resp. \f$U_{n+1}(x)\f$)
  //!     knowing the values yn = f$T_n(x)\f$ and   ynm1 = f$T_{n-1}(x)\f$, (resp.  yn = f$U_n(x)\f$ and   ynm1 = f$U_{n-1}(x)\f$).
  //!
  //! #### Example
  //!
  //! @godbolt{doc/polynomial/tchebytchev.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(tchebytchev_, tchebytchev);
}

#include <eve/module/polynomial/regular/impl/tchebytchev.hpp>
