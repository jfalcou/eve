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
#include <eve/module/core/regular/sub.hpp>
#include <eve/module/core/constant/zero.hpp>

namespace eve
{
  template<typename Options>
  struct fdim_t : elementwise_callable<fdim_t, Options>
  {
    template<eve::value T,  value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(fdim_t, fdim_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var fdim
//!   @brief `elementwise_callable` computing the positive difference between the two parameters.
//!
//!   @groupheader{Header file}
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
//!      // Regular overloads
//!      constexpr auto fdim(value auto x, value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto fdim[conditional_expr auto c](value auto x, value auto y) noexcept; // 2
//!      constexpr auto fdim[logical_value auto m](value auto x, value auto y)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [real](@ref eve::value)  arguments.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     Returns the positive difference between `x` and `y`:
//!       * if `x>y`,   `x-y` is returned,
//!       * if `x<=y`,  `+0` is returned,
//!       * otherwise a `Nan` is returned.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/fdim)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/fdim.cpp}
//! @}
//================================================================================================
  inline constexpr auto fdim = functor<fdim_t>;

  namespace detail
  {

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    fdim_(EVE_REQUIRES(cpu_), O const &, T a, T b) noexcept
    {
      return if_else(a >= b, sub(a, b), eve::zero);
    }
  }
}
