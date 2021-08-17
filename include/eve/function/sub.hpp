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
  //! @addtogroup arithmetic
  //! @{
  //! @var sub
  //!
  //! @brief Callable object performing the difference of multiple values.
  //!
  //! **Required header:** `#include <eve/function/sub.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the absolute value of its parameter               |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::value auto const&... xs) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //! `xs`:  Instances of eve::value
  //!
  //! **Return value**
  //!
  //! A value of the [common compatible type](@ref common_compatible) of all `xs` containing the
  //! [elementwise](@ref glossary_elementwise) difference of all `xs`.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::sub
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `sub[cond](x0,xs...)` is equivalent
  //!  to `if_else(cond,sub(x0,xs...),x0)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::saturated
  //!
  //!     **Required header:** `#include <eve/function/saturated/abs.hpp>`
  //!
  //!     The expression `eve::saturated(eve::sub)(xs...)` computes the saturated difference of
  //!     all `xs`.
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_3rd, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/sub.hpp>`
  //!
  //!     The expression `eve::diff_nth<N>(eve::sub)(xs...)` computes the derivative of the difference
  //!     of `xs...` over the Nth parameters.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/sub.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sub_, sub);
}

#include <eve/module/real/core/function/regular/generic/sub.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/sub.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/sub.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/sub.hpp>
#endif
