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
  //! @var absmax
  //!
  //! @brief Callable object computing the absmax operation.
  //!
  //! **Required header:** `#include <eve/function/absmax.hpp>`
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
  //!`x`, `args`:   [values](../../concepts.html#value)
  //!
  //! **Return value**
  //!
  //!the absolute value of the maximum is returned.
  //!
  //! The call `absmax(x, args...)` is equivalent to `abs(max(x, args...))`
  //!
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
  //!     **Required header:**  `#include <eve/function/pedantic/absmax.hpp>`
  //!
  //!     The call `eve::pedantic(eve::absmax)(x, args...)` is equivalent to `eve::abs(eve::pedantic(eve::max)(x, args...))`
  //!
  //!  * eve::numeric
  //!
  //!     **Required header:**  `#include <eve/function/numeric/absmax.hpp>`
  //!
  //!     The call `eve::numeric(eve::absmax)(x, args...) is equivalent to `eve::abs(eve::numeric(eve::max)(x, args...))`
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** ` #include <eve/function/diff/absmax.hpp>`
  //!
  //!     The expression `diff_nth<N>(absmax)(x,args,...)` computes the partial
  //!      derivative relative to the Nth parameter. If the parameters are \f$x_1, ..., x_n\f$ and
  //!      their absmax is \f$m\f$, the value returned is elementwise \f$\mathrm{sign}(x_N)\f$ if \f$m\f$ is equal to \f$|x_N|\f$ else 0.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/absmax.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(absmax_, absmax);
}

#include <eve/module/real/core/function/regular/generic/absmax.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/absmax.hpp>
#endif
