//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  template<typename Options>
  struct log_abs_t : elementwise_callable<log_abs_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(log_abs_t, log_abs_);
  };

//================================================================================================
//! @addtogroup math_log
//! @{
//! @var log_abs
//!
//! @brief Callable object computing the natural logarithm of the absolute value of the input.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      T log_abs(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   Returns [elementwise](@ref glossary_elementwise) the natural logarithm  of
//!   the absolute value of the input.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/log_abs.cpp}
//!  @}
//================================================================================================
inline constexpr auto log_abs = functor<log_abs_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
      log_abs_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
    {
      return eve::log(eve::abs(x));
    }
  }
}
