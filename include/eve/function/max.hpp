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
  //! @var max
  //!
  //! @brief Callable object computing the max operation.
  //!
  //! **Required header:** `#include <eve/function/max.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the max operation   |
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
  //!  Higher-order function generating a masked version of eve::max
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `max[cond](x, ...)` is equivalent to `if_else(cond,max(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `pedantic`
  //!
  //!     **Required header:**  #include <eve/function/pedantic/max.hpp>
  //!  
  //!     The call `pedantic(max)(x,args,...)`  ensures the conformity to the standard behaviour, that is
  //!      for two parameters  (on an  [element-wise](../../../glossary.html#value) basis)
  //!      to be semanticaly equivalent to:
  //!      `(x < y) ? y : x` and this behaviour is also ensured on n parameters calls as if this scheme
  //!      was recursively used.
  //!  
  //!  * `numeric`
  //!
  //!     **Required header:**  #include <eve/function/numeric/max.hpp>
  //!  
  //!     The call `numeric(max)(x,args,...)`  ensures that  if any element of the inputs is not a `Nan`, the corresponding
  //!      output element will not be a `Nan`.
  //!  
  //!  * `diff`
  //!
  //!     **Required header:**  #include <eve/function/diff/max.hpp>
  //!  
  //!     The expression `diff< N >(max)(x,args,...)` computes the partial
  //!      derivative relative to the Nth parameter. If the parameters are \f$x_1, ..., x_n\f$ and
  //!      their maximum is \f$m\f$, the value returned is 1 if \f$m\f$ is equal to \f$x_N\f$ and otherwise 0.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/max.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(max_, max);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/max.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/max.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/max.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/max.hpp>
#endif
