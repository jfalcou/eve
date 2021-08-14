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
  //! @var min
  //!
  //! @brief Callable object computing the min operation.
  //!
  //! **Required header:** `#include <eve/function/min.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the min operation   |
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
  //!`x`, `args`, ...
  //!:   [values](../../concepts.html#value)
  //!
  //! **Return value**
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
  //!  Higher-order function generating a masked version of eve::min
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `min[cond](x, ...)` is equivalent to `if_else(cond,min(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/min.hpp>`
  //!  
  //!     The call `pedantic(min)(x, args, ...)`  ensures the conformity to the standard behaviour, that is
  //!      for two parameters (on an  [element-wise](@ref glossary_elementwise) basis) semanticaly equivalent to:
  //!      `(x < y) ? x : y` and this behaviour is also ensured on n parameters calls as if this scheme
  //!      was recursively used.
  //!  
  //!  * eve::numeric
  //!
  //!     **Required header:** `#include <eve/function/numeric/min.hpp>`
  //!  
  //!     The call `numeric(max)(x,args,...)`  ensures that  if any element of the inputs is not a `Nan`, the corresponding
  //!      output element will not be a `Nan`.
  //!  
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/min.hpp>`
  //!  
  //!     The expression `diff< N >(min)(x,args,...)` computes the partial
  //!      derivative relative to the Nth parameter. If the parameters are \f$x_1, ..., x_n\f$ and
  //!      their minimum is \f$m\f$, the value returned is elementwise 1 if \f$m\f$ is equal to \f$x_N\f$ else 0.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/min.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(min_, min);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/min.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/min.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/min.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/min.hpp>
#endif
