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
  struct cyl_bessel_y0_t : elementwise_callable<cyl_bessel_y0_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr
    T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(cyl_bessel_y0_t, cyl_bessel_y0_);
  };

//================================================================================================
//! @addtogroup bessel
//! @{
//!   @var cyl_bessel_y0
//!   @brief `elementwise_callable` object computing the Bessel function of the second kind,
//!   \f$ Y_0(x)=\frac2{\pi}\int_{1}^{\infty}\frac{\cos x\tau}
//!   {\sqrt{\tau^2-1}}\,\mathrm {d} \tau\f$.
//!
//!   It is a solution of \f$ x^{2}y''+xy'+x^2y=0\f$ for which \f$ y(0) = \infty\f$.
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
//!      constexpr auto cyl_bessel_y0(floating_value auto x) -> decltype(x)           noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto cyl_bessel_y0[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto cyl_bessel_y0[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: positive [floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of \f$\displaystyle Y_0(x)=\frac2{\pi}\int_{1}^{\infty}\frac{\cos x\tau}
//!       {\sqrt{\tau^2-1}}\,\mathrm {d} \tau\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/special_functions/cyl_neumann)
//!   *  [Wikipedia: Bessel Functions](https://en.wikipedia.org/wiki/Bessel_function)
//!   *  [DLMF: Bessel Functions](https://dlmf.nist.gov/10.2)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/bessel/cyl_bessel_y0.cpp}
//================================================================================================
  inline constexpr auto cyl_bessel_y0 = functor<cyl_bessel_y0_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/bessel/regular/impl/cyl_bessel_y0.hpp>
