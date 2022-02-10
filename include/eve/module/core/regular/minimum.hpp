/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/if_else.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup reduction
  //! @{
  //! @var minimum
  //!
  //! @brief Callable object computing minimal element.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | computes the minimal element of a real value               |
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
  //!`x`:   a [real value](@ref eve::real_value)
  //!
  //! **Return value**
  //!
  //!returns a [scalar value](@ref eve::scalar_value) containing the minimal element
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::minimum
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `minimum[cond](x)` is equivalent to `minimum(if_else(cond, x, valmax(as(x))))`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/minimum.cpp}
  //!
  //!  @}
  //================================================================================================
 EVE_MAKE_CALLABLE(minimum_, minimum);
}

#include <eve/arch.hpp>
#include <eve/module/core/regular/impl/minimum.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/minimum.hpp>
#endif

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/minimum.hpp>
#endif
