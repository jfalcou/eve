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
  //! @var maxabs
  //!
  //! @brief Callable object computing the maxabs operation.
  //!
  //! **Required header:** `#include <eve/function/maxabs.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the maxabs operation   |
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
  //!  * If `|x| >  |y|`,  `|x|` is returned.
  //!  * If `|x| <  |y|`,  `|y|` is returned.
  //!  * Otherwise `max(|x|, |y|)` is returned.
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
  //!  Higher-order function generating a masked version of eve::maxabs
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `maxabs[cond](x, ...)` is equivalent to `if_else(cond,maxabs(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/maxabs.hpp>`
  //!
  //!     The behaviour is the same except that if  `|x| == |y|`, `pedantic(max)` is used.
  //!
  //!  * eve::numeric
  //!
  //!     **Required header:** `#include <eve/function/numeric/maxabs.hpp>`
  //!
  //!      The behaviour is the same except that if  `|x| == |y|`, `numeric(max)` is used.
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/maxabs.hpp>`
  //!
  //!     The expression `diff< N >(maxabs)(x,args,...)` computes the partial
  //!      derivative relative to the Nth parameter. If the parameters are \f$x_1, ..., x_n\f$ and
  //!      their maxabs is \f$m\f$, the value returned is elementwise \f$\mathrm{sign}(x_N)\f$ if \f$m\f$ is equal to \f$|x_N|\f$ else 0.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/maxabs.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(maxabs_, maxabs);
}

#include <eve/module/real/core/function/regular/generic/maxabs.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/maxabs.hpp>
#endif
