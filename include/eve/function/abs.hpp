//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  /// @addtogroup arithmetic
  /// @{
  /// @var abs
  ///
  /// **Required header:** `#include <eve/function/abs.hpp>`
  ///
  /// Function object representing the computation of the absolute value.
  ///
  /// **Member functions:**
  ///
  /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  ///  template<value T> auto operator()( T x ) const noexcept;
  /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ///
  /// Performs the  [element-wise](../../../glossary.html#element-wise_) absolute value operation
  /// on its parameter.
  ///
  /// #### Parameters
  /// `x` : An instance of eve::value
  ///
  /// #### Return value
  ///
  /// A value with the same type as `x` containing the [element-wise](../../../glossary.html#value)
  /// absolute value of `x` if it is representable in this type. More specifically, for signed
  /// integers the absolute value of eve::valmin is not representable and the result is undefined.
  ///
  /// @warning  `abs` is also a standard library function name and there possibly exists a C macro
  /// version which may be called instead of the **EVE** version.<br/>
  /// To avoid this, use the eve::abs notation.
  ///
  /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  /// template<conditional_expression C> auto operator[]( C cond ) const noexcept;
  /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ///
  /// Higher-order function generating a masked version of eve::abs
  ///
  /// #### Parameters
  /// `cond` : conditional expression
  ///
  /// #### Return value
  ///
  /// A Callable object so that the expression `abs[cond](x)` is equivalent to `if_else(cond,abs(x),x)`
  ///
  /// ### Supported decorators
  ///
  ///  * eve::saturated
  ///
  ///    **Required header:** `#include <eve/function/saturated/abs.hpp>`
  ///
  ///    The expression saturated(abs)(x) computes a saturated absolute value of `x`.
  ///    Contrary to the regular case, this guarantees that the result is element-wise greater or
  ///    equal than 0. More specifically, for any signed integer value `x`, the expression
  ///    `saturated(abs)(valmin(as(x)))` evaluates to `valmax(as(x))`.
  ///
  ///  * eve::diff
  ///
  ///    **Required header:** `#include <eve/function/diff/abs.hpp>`
  ///
  ///    The expression `diff(abs)(x)` computes the derivative of the function at `x`.
  ///
  /// ### Example
  ///
  /// @include{lineno} doc/core/abs.cpp
  ///
  /// Expected output:
  ///
  /// @include abs.out.html
  ///
  /// @}
  //================================================================================================
  EVE_MAKE_CALLABLE(abs_, abs);
}

#include <eve/module/real/core/function/regular/generic/abs.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/real/core/function/regular/simd/x86/abs.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/real/core/function/regular/simd/ppc/abs.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/real/core/function/regular/simd/arm/neon/abs.hpp>
#endif
