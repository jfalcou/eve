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
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/regular/csc.hpp>

namespace eve
{
  template<typename Options>
  struct cscpi_t : elementwise_callable<cscpi_t, Options, quarter_circle_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cscpi_t, cscpi_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var cscpi
//! @brief `elementwise_callable` object computing the cosecant in \f$\pi\f$ multiples.
//!
//!   @groupheader{Header file}
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
//!      constexpr auto cscpi(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto cscpi[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto cscpi[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto cscpi[quarter_circle](floating_value auto x)          noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`: [floating value](@ref eve::floating_value).
//!      * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!      * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. The call `cscpi(x)` is semantically equivalent to \f$\csc(\pi x)\f$.
//!       In particular:
//!         * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!         * If the element is \f$\pm\infty\f$, Nan is returned.
//!         * If the element is a `Nan`, `NaN` is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/cscpi.cpp}
//================================================================================================
  inline constexpr auto cscpi = functor<cscpi_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T cscpi_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(O::contains(quarter_circle))
        return csc[quarter_circle](a0 * pi(eve::as<T>()));
      else
      {
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return rec[pedantic](a0);
          if( is_flint(a0) || is_not_finite(a0) ) return nan(eve::as<T>()); // nan or Inf input
        }
        T x = abs(a0);
        if constexpr( simd_value<T> )
        {
          x = if_else(is_nez(a0) && (is_not_finite(x) || is_flint(x)), eve::allbits, x);
        }
        auto [fn, xr, dxr] = rem2(x);
        return rec[pedantic](sin_finalize(bitofsign(a0), quadrant(fn), xr, dxr));
      }
    }
  }
}
