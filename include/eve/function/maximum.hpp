/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup reduction
  //! @{
  //! @var maximum
  //!
  //! @brief Callable object computing maximal element.
  //!
  //! **Required header:** `#include <eve/function/maximum.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | computes the maximal element of a real value               |
  //! | `operator[]` | Construct a masked version of current function object      |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( real_value x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   a [real value](@ref real_value)
  //!
  //! **Return value**
  //!
  //!returns a [scalar value](@ref scalar_value) containing the maximal element
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::maximum
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `maximum[cond](x)` is equivalent to `maximum(if_else(cond, x, valmin(as(x))))`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/maximum.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(maximum_, maximum);
}

#include <eve/arch.hpp>
#include <eve/module/real/algorithm/function/regular/generic/maximum.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/algorithm/function/regular/simd/arm/neon/maximum.hpp>
#endif
