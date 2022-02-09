//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/pedantic.hpp>
#include <eve/module/core/regular/numeric.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup arithmetic
  //! @{
  //! @var absmax
  //!
  //! @brief Callable object computing the absmax operation.
  //!
  //! **Required header:** #include <eve/module/core.hpp>
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the absmax operation                                       |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value ...Ts> auto operator()( T x,Ts... args ) const noexcept
  //!                                       requires (compatible_values< T, Ts > && ...);
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `args`:   [values](@ref eve::value)
  //!
  //! **Return value**
  //!
  //!the [elementwise](@ref glossary_elementwise) absolute value of the maximum is returned.
  //!
  //! The call `absmax(x, args...)` is equivalent to `abs(max(x, args...))`
  //!
  //!
  //!The result type is the [common compatible type](@ref common_compatible) of the parameters.
  //!
  //!@warning
  //!   If any element of the inputs is a `Nan`, the corresponding output element is system-dependent.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::absmax
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `absmax[cond](x, ...)` is equivalent to `if_else(cond,absmax(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!
  //!     The call `eve::pedantic(eve::absmax)(x, args...)` is equivalent to `eve::abs(eve::pedantic(eve::max)(x, args...))`
  //!
  //!  * eve::numeric
  //!
  //!
  //!     The call `eve::numeric(eve::absmax)(x, args...) is equivalent to `eve::abs(eve::numeric(eve::max)(x, args...))`
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_3rd, eve::diff_nth
  //!
  //!
  //!     The expression `diff_nth<N>(absmax)(x,args,...)` computes the partial
  //!      derivative relative to the Nth parameter. If the parameters are \f$x_1, ..., x_n\f$ and
  //!      their absmax is \f$m\f$, the value returned is elementwise \f$\mathrm{sign}(x_N)\f$ if \f$m\f$ is equal to \f$|x_N|\f$ else 0.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/absmax.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(absmax_, absmax);
}

#include <eve/module/core/regular/impl/absmax.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/absmax.hpp>
#endif
