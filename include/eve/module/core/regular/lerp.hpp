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
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/fnma.hpp>


namespace eve
{
  template<typename Options>
  struct lerp_t : elementwise_callable<lerp_t, Options, pedantic_option>
  {
    template<value T,  value U,  value V>
    requires(eve::same_lanes_or_scalar<T, U, V>)
    constexpr EVE_FORCEINLINE common_value_t<T, U, V> operator()(T a, U b, V c) const
    { return EVE_DISPATCH_CALL(a, b, c); }

    EVE_CALLABLE_OBJECT(lerp_t, lerp_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var lerp
//!   @brief Computes the  linear interpolation.
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
//!      template< eve::value T, eve::value U, eve::floating_value V >
//!      eve::common_value_t<T, U> lerp(T x, U y, V t) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:   [real](@ref eve::value) arguments.
//!     * `t`:  [real floating](@ref eve::floating_value).  argument
//!
//!    **Return value**
//!
//!    The value of the interpolation (or extrapolation)  between `x` and `y` is returned.
//!    The call is semantically equivalent to `x+t*(y-x)` but uses fma opportunities.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/lerp.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::lerp[mask](x, ...)` provides a masked
//!     version of `lerp` which is
//!     equivalent to `if_else(mask, lerp(x, ...), x)`
//!
//!   * eve::pedantic
//!
//!     when `lerp[pedantic](a, b, t)` pedantic version of fma is used internally
//! @}
//================================================================================================
  inline constexpr auto lerp = functor<lerp_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    lerp_(EVE_REQUIRES(cpu_), O const & o, T const &a,  T const &b,  T const &t) noexcept
    {
      return fma[o](t, b, fnma[o](t, a, a));
    }
  }
}
