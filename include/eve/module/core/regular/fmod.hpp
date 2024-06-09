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
    template<eve::floating_value T0, floating_value T1>
    requires(eve::same_lanes_or_scalar<T0, T1>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1> operator()(T0 t0, T1 t1) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1);
    }

    EVE_CALLABLE_OBJECT(fmod_t, fmod_);
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
//!      template< eve::floating_value T,  eve::floating_value U>
//!      eve::common_value_t<T, U> fmod(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:   [real](@ref eve::floating_value) argumentx.
//!
//!   **Return value**
//!
//!      Return the remainder after division division of `x` by `y` and mimick
//!      the behaviour of std::fmod.
//!
//!      In particular:
//!
//!      * If `x` is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If `x` is \f$\pm\inf\f$ or `NaN`, `NaN` is returned.
//!      * If `y` is \f$\pm0\f$, `NaN` is returned.
//!      * If `y` is \f$\pm\inf\f$ and `x` is finite, `x`is returned.
//!
//! @}
//================================================================================================
  inline constexpr auto fmod = functor<fmod_t>;

  namespace detail
  {
    template<typename T, callable_options O> EVE_FORCEINLINE constexpr auto
    fmod_(EVE_REQUIRES(cpu_), O const &, T const& a, T const& b) noexcept
    {
      return if_else(is_unordered(a, b) || is_infinite(a) || is_eqz(b),
                     allbits,
                     if_else(is_eqz(a)||is_infinite(b), a, fnma(b, div[toward_zero2](a, b), a)));
    }

  }
}
