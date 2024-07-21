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
#include <eve/module/math.hpp>

namespace eve
{
  template<typename Options>
  struct sph_bessel_j0_t : elementwise_callable<sph_bessel_j0_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr
    T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(sph_bessel_j0_t, sph_bessel_j0_);
  };

//================================================================================================
//! @addtogroup bessel
//! @{
//!   @var sph_bessel_j0
//!   @brief Computes the spherical Bessel function of the first kind,
//!   \f$ j_{0}(x)= \sqrt{\frac\pi{2x}}J_{1/2}(x) \f$.
//!
//!   It is the solution of \f$ x^{2}y''+2xy'+x^2 y=0\f$ for which \f$ y(0) = 1\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/bessel.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto sph_bessel_j0(floating_value auto x) -> decltype(x)           noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sph_bessel_j0[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto sph_bessel_j0[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [Floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of \f$\displaystyle j_{0}(x)=\frac{\sin x }{x}\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!   @groupheader{Example}
//!   @godbolt{doc/bessel/sph_bessel_j0.cpp}
//================================================================================================
//================================================================================================
  inline constexpr auto sph_bessel_j0 = functor<sph_bessel_j0_t>;
//================================================================================================
//! @}

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T sph_bessel_j0_(EVE_REQUIRES(cpu_), O const&, T x)
    {
      return sinc(x);
    }
  }
}
