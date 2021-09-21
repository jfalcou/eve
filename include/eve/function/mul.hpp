//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup operators
  //! @{
  //! @var mul
  //!
  //! @brief Callable object computing the mul operation.
  //!
  //! **Required header:** `#include <eve/function/mul.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the mul operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value ...Ts> auto operator()( T x,Ts... args ) const noexcept
  //!                                  requires (compatiblevalues< T, Ts > && ...);
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `args`:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Return the multiplication of the [values](@ref eve::value).
  //!
  //! The result type is the [common compatible type](@ref common_compatible) of the parameters.
  //!
  //! The call `mul(x, args, ...)` is equivalent to `(x * args * ...)` if `x` or one of the `args`
  //! is an  [simd value](@ref eve::simd_value).
  //!
  //!@warning
  //!   Although the infix notation with `*` is supported for two parameters, the `*` operator on
  //!   standard scalar types is the original one and so can lead to automatic promotion.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::mul
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `mul[cond](x, ...)` is equivalent to `if_else(cond,mul(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::saturated
  //!
  //!     **Required header:** `#include <eve/function/saturated/mul.hpp>`
  //!
  //!     The call `saturated(mul)(x, args...)` computes the saturated  multiplication of `x` and `args...`. The saturation is obtained in the
  //!     [common compatible type](@ref common_compatible) of the N parameters. The computation is done as if all arguments were
  //!     converted to this type and the saturated multiplication applied recursively on all parameters. No overflow occurs.
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_3rd, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/mul.hpp>`
  //!
  //!     The expression `diff_< N >(mul)(x,args,...)` computes the partial
  //!      diff of the function relative to the Nth parameter.
  //!
  //!      If the actual parameters are \f$x_1, ... x_n\f$ the value returned is
  //!      \f$\prod_{i \neq N} x_i\f$ if \f$1\le N \le n\f$ otherwise 0.
  //!
  //!      @warning
  //!        This is only available for floating point entries.
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/mul.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(mul_, mul);
}

#include <eve/module/real/core/function/regular/generic/mul.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/mul.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/mul.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/mul.hpp>
#endif
