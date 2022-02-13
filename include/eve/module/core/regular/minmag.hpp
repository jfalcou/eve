//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/pedantic.hpp>
#include <eve/module/core/regular/numeric.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var minmag
  //!
  //! @brief Callable object computing the minmag operation.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the minmag operation   |
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
  //!`x`, `y`:   [values](@ref eve::value)
  //!
  //! **Return value**
  //!
  //!the [elementwise](@ref glossary_elementwise) element of least absolute value is returned.
  //!
  //!For instance for two elements:
  //!
  //!  * If `|x| >  |y|`,  `y` is returned.
  //!  * If `|x| <  |y|`,  `x` is returned.
  //!  * Otherwise `min(x, y)` is returned.
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
  //!  Higher-order function generating a masked version of eve::minmag
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `minmag[cond](x, ...)` is equivalent to `if_else(cond,minmag(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!
  //!     The behaviour is the same except that if  `|x| == |y|`, `pedantic(min)` is used.
  //!
  //!  * eve::numeric
  //!
  //!
  //!     The behaviour is the same except that if  `|x| == |y|`, `numeric(min)` is used.
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!
  //!     The expression `diff< N >(minmag)(x,args,...)` computes the partial
  //!      derivative relative to the Nth parameter. If the parameters are \f$x_1, ..., x_n\f$ and
  //!      their minmag is \f$m\f$, the value returned is elementwise 1 if \f$m\f$ is equal to \f$x_N\f$ else 0.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/minmag.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(minmag_, minmag);
}

#include <eve/module/core/regular/impl/minmag.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/minmag.hpp>
#endif
