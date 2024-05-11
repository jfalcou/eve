//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/ceil.hpp>
#include <eve/module/core/regular/floor.hpp>
#include <eve/module/core/regular/nearest.hpp>
#include <eve/module/core/regular/trunc.hpp>


namespace eve
{
  template<typename Options>
  struct round_t : elementwise_callable<round_t, Options,  downward_option, upward_option,
                                        to_nearest_option, toward_zero_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    {
      return EVE_DISPATCH_CALL(v);
    }

    EVE_CALLABLE_OBJECT(round_t, round_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var round
//!   @brief Computes the integer nearest to the input.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T >
//!      T round(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) argument.
//!
//!    **Return value**
//!
//!    The integer nearest to `x`.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/round.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::round[mask](x)` provides a masked version of `eve::round` which is
//!     equivalent to `if_else (mask, round(x), x)`.
//!
//!   * eve::downward
//!
//!     The expression `eve::downward(eve::round)(x)` is equivalent to `eve::floor(x)`.
//!
//!   * eve::upward
//!
//!     The expression `eve::upward(eve::round)(x)` is equivalent to `eve::ceil(x)`.
//!
//!   * eve::to_nearest
//!
//!     The expression `to_nearest(eve::round)(x)` is equivalent to `eve::nearest(x)`.
//!
//!   * eve::toward_zero
//!
//!     The expression `eve::toward_zero(eve::round)(x)` is equivalent to `eve::trunc(x)`.
//!
//! @}
//================================================================================================
  inline constexpr auto round = functor<round_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    round_(EVE_REQUIRES(cpu_), O const & o, T const &a) noexcept
    {
      if      constexpr( O::contains(eve::upward2)      ) return eve::ceil(a);
      else if constexpr( O::contains(eve::downward2)    ) return eve::floor(a);
      else if constexpr( O::contains(eve::toward_zero2) ) return eve::trunc(a);
      else if constexpr( O::contains(eve::to_nearest2)  ) return eve::nearest(a);
      else                                                return eve::nearest(a);
    }
  }
}
