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
  //! @var average
  //!
  //! @brief Callable object computing the average of multiple values.
  //!
  //! **Required header:** `#include <eve/function/average.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the mid-point operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y ) const noexcept requires compatible< T, U >;
  //!  template< floating_value T, floating_value ...Ts> auto operator()( T x,Ts... args ) const noexcept
  //!                                                    requires (compatiblevalues< T, Ts > && ...);
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y` or `x`, `args`, ...
  //!:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!For two parameters half the sum of `x` and `y`. No overflow occurs.
  //!
  //!For more than two parameters only floating entries are allowed and overflow is avoided.
  //!
  //! The result type is the [compatibility result](../../concept.html#compatibility) of the parameters.
  //!
  //!@warning
  //!    If `x` and `y` are [real integral values](@ref eve::value) and the sum is odd, the result
  //!    is a rounded value at a distance guaranteed
  //!    to be less than or equal to 0.5 of the average floating value, but may differ
  //!    by unity from the truncation given by `(x+y)/2`. Moreover, as some architectures provide
  //!    simd intrinsics to perform the operation, the scalar results may differ by one unit from
  //!    simd ones which are system dependent.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::average
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `average[cond](x, ...)` is equivalent to `if_else(cond,average(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/average.hpp>`
  //!
  //!     The expression `diff_nth< N >(average)(x,args...)` computes the partial
  //!      derivative of the function relative to its Nth parameter. The returned value is 0 if N is
  //!      greater that the actual number of parameters, otherwise it is the inverse of the number of parameters.
  //!
  //!      This is only available for floating point entries.
  //!
  //!  * eve::raw
  //!
  //!     when `raw(average)(x, args, ...)` is used, no provision is made to avoid overflows for more than 2 parameters.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/average.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(average_, average);
}

#include <eve/module/real/core/function/regular/generic/average.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/average.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/average.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/average.hpp>
#endif
