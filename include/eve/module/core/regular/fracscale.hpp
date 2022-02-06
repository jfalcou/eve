//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <type_traits>
#include <eve/assert.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup arithmetic
  //! @{
  //! @var fracscale
  //!
  //! @brief Callable object computing the fractional scaled part.
  //!
  //! **Required header:** `#include <eve/function/fracscale.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of the fractional scaled part             |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(floating_value auto x, int scale) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:      [floating real value](@ref eve::floating_real_value).
  //!
  //!`scale` : int or std::integral_constant of int type limited to the range [0, 15].
  //!
  //! **Return value**
  //!
  //! Returns the [elementwise](@ref glossary_elementwise) reduced part of the scaled input.
  //! The number of fraction bits retained is specified by scale. By default the internal rounding after scaling is done to nearest integer.
  //! The call is equivalent to `a0-roundscale(a0,scale)`
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::fracscale
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `fracscale[cond](x, ...)` is equivalent to `if_else(cond,fracscale(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::to_nearest, eve::toward_zero, eve::upward,  eve::downward
  //!
  //!     If d is one of these 4 decorators
  //!     The call `d(fracscale)(x)`, call is equivalent to  `a0-d(roundscale)(a0, scale)`
  //!
  //! #### Example
  //!
  //! @godbolt{doc/arithmetic/fracscale.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag
  {
    struct fracscale_;
  }

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::fracscale_), T const &, [[maybe_unused]] int s)
    {
        EVE_ASSERT(s >= 0 && s < 16, "[eve::fracscale] -  parameter s out of range [0, 15]: " << s);
    }
    template<int S, typename T>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::fracscale_), T const &, std::integral_constant<int, S> const & )
    {
        EVE_ASSERT(S >= 0 && S < 16, "[eve::fracscale] -  integral constant out of range [0, 15]: " << S);
    }
  }

  EVE_MAKE_CALLABLE(fracscale_, fracscale);
}

#include <eve/arch.hpp>
#include <eve/module/core/regular/impl/fracscale.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fracscale.hpp>
#endif
