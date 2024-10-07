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
  struct fmod_t : elementwise_callable<fmod_t, Options>
  {
    template<floating_value T0, floating_value T1>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1> operator()(T0 t0, T1 t1) const noexcept
      requires (same_lanes_or_scalar<T0, T1>)
    {
      return EVE_DISPATCH_CALL_PT((common_value_t<T0, T1>), t0, t1);
    }

    EVE_CALLABLE_OBJECT(fmod_t, fmod_);
  };


//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var fmod
//!   @brief `elementwise_callable` object mimicking the std::fmod function for floating values.
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
//!      // Regular overload
//!      constexpr auto fmod(floating_value auto x, floating_value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto fmod[conditional_expr auto c](floating_value auto x, floating_value auto y) noexcept; // 2
//!      constexpr auto fmod[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [real](@ref eve::floating_value) argumentx.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. Returns the remainder after division division of `x` by `y` and mimick
//!        the behaviour of std::fmod. In particular:
//!          * If `x` is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!          * If `x` is \f$\pm\inf\f$ or `NaN`, `NaN` is returned.
//!          * If `y` is \f$\pm0\f$, `NaN` is returned.
//!          * If `y` is \f$\pm\inf\f$ and `x` is finite, `x`is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/fmod)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/fmod.cpp}
//!
//================================================================================================
  inline constexpr auto fmod = functor<fmod_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T> EVE_FORCEINLINE constexpr auto
    fmod_(EVE_REQUIRES(cpu_), O const &, T const& a, T const& b) noexcept
    {
      return if_else(is_unordered(a, b) || is_infinite(a) || is_eqz(b),
                     allbits,
                     if_else(is_eqz(a)||is_infinite(b), a, fnma(b, div[toward_zero](a, b), a)));
    }

  }
}
