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
  //! @addtogroup arithmetic
  //! @{
  //! @var maxmag
  //!
  //! @brief Callable object computing the maxmag operation.
  //!
  //! **Required header:** `#include <eve/function/maxmag.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the maxmag operation   |
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
  //!`x`, `args`:   [values](../../concepts.html#value)
  //!
  //! **Return value**
  //!
  //!the greatest absolute value is returned.
  //!
  //!For instance for two elemnts:
  //!
  //!  * If `|x| >  |y|`,  `x` is returned.
  //!  * If `|x| <  |y|`,  `y` is returned.
  //!  * Otherwise `max(x, y)` is returned.
  //!
  //!For n parameters the result is computed as if this scheme was recursively used.
  //!
  //!The result type is the [compatibility result](../../concept.html#compatibility) of the parameters.
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
  //!  Higher-order function generating a masked version of eve::maxmag
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `maxmag[cond](x, ...)` is equivalent to `if_else(cond,maxmag(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/maxmag.hpp>`
  //!
  //!     The behaviour is the same except that if  `|x| == |y|`, `pedantic(max)` is used.
  //!
  //!  * eve::numeric
  //!
  //!     **Required header:** `#include <eve/function/numeric/maxmag.hpp>`
  //!
  //!      The behaviour is the same except that if  `|x| == |y|`, `numeric(max)` is used.
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/maxmag.hpp>`
  //!
  //!     The expression `diff< N >(maxmag)(x,args,...)` computes the partial
  //!      derivative relative to the Nth parameter. If the parameters are \f$x_1, ..., x_n\f$ and
  //!      their maxmag is \f$m\f$, the value returned is elementwise 1 if \f$m\f$ is equal to \f$x_N\f$ else 0.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/maxmag.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(maxmag_, maxmag);
}

#include <eve/module/real/core/function/regular/generic/maxmag.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/maxmag.hpp>
#endif
