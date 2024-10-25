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
  struct cyl_bessel_in_t : strict_elementwise_callable<cyl_bessel_in_t, Options>
  {
    template<eve::value N, eve::floating_value T>
    requires (same_lanes_or_scalar<N, T>)
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N> operator()(N n, T x) const noexcept
    { return EVE_DISPATCH_CALL(n, x); }

    EVE_CALLABLE_OBJECT(cyl_bessel_in_t, cyl_bessel_in_);
  };

//================================================================================================
//! @addtogroup bessel
//! @{
//!   @var cyl_bessel_in
//!   @brief `elementwise_callable` object computing the modified Bessel functions of the first kind,
//!   \f$ I_{n}(x)=\left(\frac12z\right)^n\sum_{k=0}^{\infty}{\frac{(x^2/4)^k}
//!   {k!\,\Gamma (k+n +1)}}\f$.
//!
//!   It is the solution of \f$ x^{2}y''+xy'+(x^2-n^2)y=0\f$ for which \f$ y(0) = 0\f$.
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
//!      template<value  N, floating_value T> constexpr as_wide_as_t<T,N> cyl_bessel_in(N n, T x)   noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto cyl_bessel_in[conditional_expr auto c](value auto n, floating_value auto x) noexcept; // 2
//!      constexpr auto cyl_bessel_in[logical_value auto m](value auto n, floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: order of the function (non necessarily integral),
//!     * `x`: [ floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!      1. The value of \f$\displaystyle I_{n}(x)=\left(\frac12z\right)^{\!\!n}\sum_{k=0}^{\infty}
//!         {\frac{(x^2/4)^k}{k!\,\Gamma (k+n +1)}}\f$ is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: cyl_bessel_i](https://en.cppreference.com/w/cpp/numeric/special_functions/cyl_bessel_i)
//!   *  [Wikipedia: Bessel Functions](https://en.wikipedia.org/wiki/Bessel_function)
//!   *  [DLMF: Modified Bessel Functions](https://dlmf.nist.gov/10.25)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/bessel/cyl_bessel_in.cpp}
//================================================================================================
  inline constexpr auto cyl_bessel_in = functor<cyl_bessel_in_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/bessel/regular/impl/cyl_bessel_in.hpp>
