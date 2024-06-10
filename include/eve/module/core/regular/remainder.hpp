//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/rem.hpp>

namespace eve
{
  template<typename Options>
  struct remainder_t : elementwise_callable<remainder_t, Options>
  {
    template<eve::floating_value T0, floating_value T1>
    requires(eve::same_lanes_or_scalar<T0, T1>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1> operator()(T0 t0, T1 t1) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1);
    }

    EVE_CALLABLE_OBJECT(remainder_t, remainder_);
  };


//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var fmod
//!   @brief mimick the std::fmod function for floating values.
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
//!      template< eve::value T,  eve::value U>
//!      eve::common_value_t<T, U> rem(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:   [real](@ref eve::value) arguments.
//!
//!   **Return value**
//!
//!      Return the remainder after division division of `x` by `y` and is
//!      semantically equivalent to  `x- eve::nearest(eve:div(x, y))*y`.
//!
//!      In particular:
//!
//!      * If `x` is \f$\pm\inf\f$ or `NaN`, `NaN` is returned.
//!      * If `y` is \f$\pm0\f$  \f$\pm0\f$ is returned
//!      * If `y` is `NaN`, `NaN` is returned.
//!
//! @}
//================================================================================================
  inline constexpr auto remainder = functor<remainder_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    remainder_(EVE_REQUIRES(cpu_), O const &, T const& a, T const& b) noexcept
    {
      return rem[to_nearest2](a, b);
    }
  }
}
