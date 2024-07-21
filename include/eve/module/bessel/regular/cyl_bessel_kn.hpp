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

namespace eve
{
  template<typename Options>
  struct cyl_bessel_kn_t : strict_elementwise_callable<cyl_bessel_kn_t, Options>
  {
    template<eve::value N, eve::floating_value T>
    requires (same_lanes_or_scalar<N, T>)
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N> operator()(N n, T x) const noexcept
    { return EVE_DISPATCH_CALL(n, x); }

    EVE_CALLABLE_OBJECT(cyl_bessel_kn_t, cyl_bessel_kn_);
  };

//================================================================================================
//! @addtogroup bessel
//! @{
//!   @var cyl_bessel_kn
//!   @brief `elementwise_callable` object computing the modified Bessel function of the second kind,
//!    \f$ K_n(x)=\frac{\Gamma(n+1/2)(2x)^n}{\sqrt\pi} \int_{0}^{\infty}\frac{\cos\tau}
//!   {(\tau^2+x^2)^{n+1/2}}\,\mathrm{d}\tau\f$.
//!
//!   It is the solution of \f$ x^{2}y''+xy'-(x^2+n^2)y=0\f$ for which \f$ y(0) = \infty\f$.
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
//!      template<value N, floating_value T> constexpr as_wide_as_t<T,N> cyl_bessel_kn(N n, T x)    noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto cyl_bessel_kn[conditional_expr auto c](value auto n, floating_value auto x) noexcept; // 2
//!      constexpr auto cyl_bessel_kn[logical_value auto m](value auto n, floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: order of the function (non necessarily integral)
//!     * `x`: [floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!      1. The value of \f$\displaystyle K_n(x)=\frac{\Gamma(n+1/2)(2x)^n}{\sqrt\pi}
//!         \int_{0}^{\infty}\frac{\cos\tau}{(\tau^2+x^2)^{n+1/2}}\,\mathrm{d}\tau\f$ is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/special_functions/cyl_bessel_k)
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Bessel_function)
//!   *  [DLMF](https://dlmf.nist.gov/10.25)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/bessel/cyl_bessel_kn.cpp}
//================================================================================================
  inline constexpr auto cyl_bessel_kn = functor<cyl_bessel_kn_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/bessel/regular/impl/cyl_bessel_kn.hpp>
