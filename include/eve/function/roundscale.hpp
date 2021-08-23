//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup arithmetic
  //! @{
  //! @var roundscale
  //!
  //! @brief Callable object computing the scaled rouding.
  //!
  //! **Required header:** `#include <eve/function/roundscale.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of the scaled rouding                     |
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
  //! Returns the [elementwise](@ref eve::glossary_elmentwise) rounding of the scaled input.
  //! The number of fraction bits retained is specified by scale. By default the internal rounding after scaling is done to nearest integer.
  //! The call is equivalent to `ldexp(round(ldexp(a0,scale),-scale))`
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::roundscale
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `roundscale[cond](x, ...)` is equivalent to `if_else(cond,roundscale(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::to_nearest, eve::toward_zero, eve::upward,  eve::downward
  //!
  //!     If d is one of these 4 decorators
  //!     The call `d(roundscale)(x)`, call is equivalent to  `eve::ldexp(d(``eve::round``)(``eve::ldexp``(a0,scale), -scale))`
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/roundscale.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag
  {
    struct roundscale_;
  }

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::roundscale_), T const &, [[maybe_unused]] int s)
    {
        EVE_ASSERT(s >= 0 && s < 16, "[eve::roundscale] -  parameter s out of range [0, 15]: " << s);
    }
    template<int S, typename T>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::roundscale_), T const &, std::integral_constant<int, S> const & )
    {
        EVE_ASSERT(S >= 0 && S < 16, "[eve::roundscale] -  integral constant out of range [0, 15]: " << S);
    }
  }

  EVE_MAKE_CALLABLE(roundscale_, roundscale);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/roundscale.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/roundscale.hpp>
#endif
